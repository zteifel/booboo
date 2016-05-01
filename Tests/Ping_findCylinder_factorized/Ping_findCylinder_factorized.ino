// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include "declarations.h"
#include <Servo.h> // Include servo library
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"

Servo servoLeft;
Servo servoRight;

const int discardCylDist = 65;
const int horizonDist = 300;

int  measurements[stepsInFullTurn];
int  currentIndex = 0;
int  noCylinder[stepsInFullTurn];
int  stepsToCylinder;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  tone(beepPin, 2000, 500);
  servoLeft.attach(13);
  servoRight.attach(12);

  delay(2000); 
}

void loop(){
  currentIndex ++;
  currentIndex %= stepsInFullTurn;
  
  rotateStep(servoLeft, servoRight, counterClockwise);
  int m = measurePingDist();
  
  Serial.println(arrayToString(measurements, stepsInFullTurn));
  measurements[currentIndex] = m;
  if(m > discardCylDist)
    noCylinder[currentIndex] = true;
  int cyl = findCylinder(currentIndex);
  if(cyl != -1){
    Serial.println("found cyl "+String(cyl)+" steps away");
    while(cyl--){
      rotateStep(servoLeft, servoRight, clockwise);
    }
    while(measurePingDist() > 5){
      //.println("Approaching cylinder!! dist:"+String(measurePingDist()));
      moveForward(servoLeft, servoRight);
      delay(500);
    }
    stopMovement(servoLeft, servoRight);
    beep();
    delay(5000);
  }
}

// Determines the index of the best cylinder candidate
// Finds the middle of the interval containing the
// closest measured point. If that distance is too large
// to be a cylinder, check the next-to-closest interval.
// If no intervals can be cylinders, call
// getIndexOfLargestOpenInterval to get a free new direction
// to explore.
int findCylinder(int maxIndex){
  if(maxIndex < 10)
    return -1;
  const int l = stepsInFullTurn;

  while(true){
    int nearestIndex = getIndexMin(measurements, noCylinder, maxIndex);
    
    Serial.println("Nearest index found: "+String(nearestIndex));
    if(nearestIndex == -1){
      //return getIndexOfLargestOpenInterval();
      return -1;
    }
    int iL = nearestIndex-1;
    int iR = nearestIndex+1;
    int intervalLength = 0;
  
    while(abs(measurements[nearestIndex] - measurements[iL]) < 5){
      iL--;
      intervalLength++;
      if(iL<0){
        return -1; //error();
      }
    }
    while(abs(measurements[nearestIndex] - measurements[iR]) < 5){
      iR++;
      intervalLength++;
      if(iR >= maxIndex){ // TODO Consider > instead of >=
        return -1; //Should continue measuring
      }
    }

    
    Serial.println("intervalLength: "+String(intervalLength));

    if(intervalLength <= 5){ // TODO Experimenting with the threshold
      return maxIndex-(iL + iR)/2;
    } else {
      for(int i=iL; i<iR; i=nextIndex(i,l)){ // TODO consider the edges
        noCylinder[i] = true; 
      }
    }
  }
}

// Index of the broadest open horizon.
int getIndexOfLargestOpenInterval(){
  int lenLargest = 0;
  int iLeftLargest = 0;
  int iRightLargest = 0;
  int nbrOfRightChecks = 0;  

  int iLeft;
  int iRight;
  int i=-1;
  while(true) {
    //Take step into possible new intervall:
    iLeft = nextIndex(i,stepsInFullTurn);
    
    iRight = iLeft;
    
    int intervalWidth = 0;
    while(measurements[iLeft] < horizonDist){
      iLeft = prevIndex(iLeft,stepsInFullTurn);
      intervalWidth++;
    }
    while(measurements[iRight] < horizonDist){
      iRight = nextIndex(iRight,stepsInFullTurn);
      intervalWidth++;
      nbrOfRightChecks++;
    }
    if(intervalWidth > lenLargest){
      lenLargest = intervalWidth;
      iLeftLargest = iLeft;
      iRightLargest = iRight;
    }
    
    i=iRight;
    
    // When all points have been examined, continue!
    if(nbrOfRightChecks > stepsInFullTurn){
      break;
    }
  }
  
  return iLeftLargest<iRightLargest ? 
    (iRightLargest + iRightLargest)/2 : 
    ((iRightLargest + iRightLargest + stepsInFullTurn)/2) % stepsInFullTurn;
}
