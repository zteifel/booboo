// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"

const int discardCylDist = 65;
const int horizonDist = 100;
const int extraSwipeSteps = 3;
const int noCylFound = -1;
const int rotationSpeed = 25;
const int msInFullTurn = 8000;
const int nMeasurements = 30;
const int msPerStep = msInFullTurn / nMeasurements;

int  measurements[nMeasurements];
int  noCylinder[nMeasurements];
int  stepsToCylinder;

void setup() {
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(pingPin, INPUT);
  tone(beepPin, 2000, 500);
  servoLeft.attach(13);
  servoRight.attach(12);
  delay(2000); 
}

void loop(){
  // Clear measurement data
  resetMeasurements();
  
  // Rotate continually and measure
  rotate(counterClockwise, rotationSpeed);
  for(int i=0; i<nMeasurements; i++){
    measurements[i] = measurePingDist();
    delay(msPerStep-7); // -7 since this is the delay in the measurement
  }
  stopMovement();
  
  // Update the auxiliary array
  for(int i=0; i<nMeasurements; i++){
    if(measurements[i] > discardCylDist){
      noCylinder[i] = true;
    }
  }
  
  beep2(); // DEBUG
  Serial.println("Entering findCylinder"); // DEBUG
  
  // Run main search algorithm
  int headingIndex = findCylinder();
  
  beep3(); // DEBUG
  
  if(headingIndex == noCylFound){
    Serial.println("Entering getIndexOfLargestOpenInterval"); // DEBUG
    headingIndex = getIndexOfLargestOpenInterval();
  }
  
  Serial.println("Entering rotation"); // DEBUG
  
  // Rotate towards cylinder/large open space
  if(headingIndex != noCylFound){
    if(headingIndex <= nMeasurements/2){
      rotate(counterClockwise, rotationSpeed);
      delay(msPerStep * headingIndex);
    }else{
      rotate(clockwise, rotationSpeed);
      delay(msPerStep * (nMeasurements - headingIndex));
    }
  }
  
  // Move forward a while or until collision
  moveForward();
  for(int i=0; i < 5000/100; i++){
    if(measurePingDist() <= 5){
      break;
    }
    delay(100);
  }
  stopMovement();
  
  // Signal done and wait
  beep();
  delay(5000); 
}

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
      noCylinder[i]=false;
    }
}

bool couldIntervalBeCylinder(int intervalLength, int intervalDist){
  // TODO Experimenting with the condition, use intervalDist
  return intervalLength <= 5;
}

// Determines the index of the best cylinder candidate
// Finds the middle of the interval containing the
// closest measured point. If that distance is too large
// to be a cylinder, check the next-to-closest interval.
// If no intervals can be cylinders, call
// getIndexOfLargestOpenInterval to get a free new direction
// to explore.
int findCylinder(){
  while(true){
    Serial.println("findCylinder: outer loop"); // DEBUG
    int nearestIndex = getIndexMin(measurements, noCylinder, nMeasurements);
    
    if(nearestIndex == noCylFound){
      return -1;
    }
    
    int iL = prevIndex(nearestIndex, nMeasurements);
    int iR = nextIndex(nearestIndex, nMeasurements);
    int intervalLength = 0;
  
    while(abs(measurements[nearestIndex] - measurements[iL]) < 5){
      iL = prevIndex(iL, nMeasurements);
      intervalLength++;
      Serial.println("findCylinder: inner loop 1"); // DEBUG
    }
    while(abs(measurements[nearestIndex] - measurements[iR]) < 5){
      iR = nextIndex(iR, nMeasurements);
      intervalLength++;
      Serial.println("findCylinder: inner loop 2"); // DEBUG
    }
    
    if(couldIntervalBeCylinder(intervalLength, measurements[nearestIndex])){
      return periodicBoundary(iL + intervalLength/2, nMeasurements);
    } else {
      for(int i=iL+1; i<iR; i=nextIndex(i, nMeasurements)){
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
    iLeft = nextIndex(i,nMeasurements);
    
    iRight = iLeft;
    
    int intervalWidth = 0;
    while(measurements[iLeft] > horizonDist){
      iLeft = prevIndex(iLeft,nMeasurements);
      intervalWidth++;
    }
    while(measurements[iRight] > horizonDist){
      iRight = nextIndex(iRight,nMeasurements);
      intervalWidth++;
      nbrOfRightChecks++;
    }
    if(intervalWidth > lenLargest){
      lenLargest = intervalWidth;
      iLeftLargest = iLeft;
      iRightLargest = iRight;
    }
    
    i = nextIndex(iRight, nMeasurements);
    nbrOfRightChecks++;
    
    // When all points have been examined, continue!
    if(nbrOfRightChecks > nMeasurements){
      break;
    }
  }
  
  return periodicBoundary(iLeftLargest + lenLargest/2, nMeasurements);
}
