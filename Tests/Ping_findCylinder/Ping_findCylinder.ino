// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
    
Servo servoLeft;
Servo servoRight;

const int pingPin = 8;
const int stepsInFullTurn = 25;
const int discardCylDist = 65;
const int horizonDist = 300;

long      pingDist;
int       measurements[stepsInFullTurn];
int       noCylinder[stepsInFullTurn]; //////////// <-- Använd detta!!!!!!!!!

const bool clockwise = true;
const bool counterClockwise = false;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  tone(4, 2000, 500);
  servoLeft.attach(13);
  servoRight.attach(12);

  delay(2000); 
}

void loop(){
	measure();
  Serial.println(arrayToString(measurements,stepsInFullTurn));
  delay(2000); 
}

// Performs full turn and saves measurements to array
// Notes measurements that are too far to be a cylinder
void measure(){ 
  for(int i=0; i<stepsInFullTurn; i++){ 
    rotateStep(counterClockwise);
    int m = measurePingDist();
    measurements[i] = m;
    if(m < discardCylDist)
      noCylinder[i] = true;
  }
}

String arrayToString(int array[], int arrayLength)
{
  String s = "[ ";
  for(int i=0; i < arrayLength; i++){
    s+=String(array[i])+" ";
  }
  return s + "]";
}

// Perform measurement with ping sensor
// Returns distance in cm
long measurePingDist(){
  long duration, cm;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  return microsecondsToCentimeters(duration);
}

// Rotates one step clockwise or counter-clockwise
void rotateStep(bool clockwise) {
  if(clockwise){
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
  } else {
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
  }
  delay(100);
  stopMovement();
  delay(100);
}

// Halts robot
void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

long microsecondsToCentimeters(long microseconds){
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

// Gives previous index with wrap-around
int prevIndex(int index, int arrayLength){
  return (index+arrayLength-1) % arrayLength;
}

// Gives next index with wrap-around
int nextIndex(int index, int arrayLength){
  return (index+1) % arrayLength;
}

// Determines the index of the best cylinder candidate
// Finds the middle of the interval containing the
// closest measured point. If that distance is too large
// to be a cylinder, check the next-to-closest interval.
// If no intervals can be cylinders, call
// getIndexOfLargestOpenInterval to get a free new direction
// to explore.
int findCylinder(){
  //stepsInFullTurn;
  //measurements;
  const int l = stepsInFullTurn;

  while(1){
    int nearestIndex = getIndexMin();

    if(nearestIndex = -1){
      return getIndexOfLargestOpenInterval();
    }
    
    int iL = prevIndex(nearestIndex,l);
    int iR = nextIndex(nearestIndex,l);
    int intervalLength = 0;
  
    while(abs(measurements[iL])-abs(measurements[iR]) < 5){
      iL = prevIndex(iL,l);
      intervalLength++;
    }
    while(abs(measurements[iR])-abs(measurements[iR]) < 5){
      iR = prevIndex(iR,l);
      intervalLength++;
    }

    if(intervalLength < 5){
      return (int)(iL+intervalLength/2) % intervalLength;
    } else {
      for(int i=iL; i<iR; i++){
        noCylinder[i] = true; 
      }
    }
  }
}

// Index of the closest measured distance
int getIndexMin(){
  int minVal = 500;   //Max
  int iMinVal = -1;
  
  for(int i=0; i<stepsInFullTurn; i++){
    if( !noCylinder[i] && (minVal > measurements[i]) ){
      iMinVal = i;
      minVal = measurements[i];
    }
  }
  return iMinVal;
}

// Index of the broadest open horizon.
int getIndexOfLargestOpenInterval(){
  int lenLargest = 0;
  int iLeftLargest = 0;
  int iRightLargest = 0;
  int startIndex = 0;

  while(measurements[startIndex] >= horizonDist){
    startIndex = prevIndex(startIndex,stepsInFullTurn);
  }
  
  int iLeft = startIndex;
  int iRight;
  
  for(int i=0; i<stepsInFullTurn; i++){  
    while(measurements[iLeft] < horizonDist){
      iLeft = nextIndex(iLeft,stepsInFullTurn);
    }
    iRight = iLeft;
    int intervalWidth = 0;
    while(measurements[iLeft] < horizonDist){
      iRight = nextIndex(iRight,stepsInFullTurn);
      intervalWidth++;
    }
    if(intervalWidth > lenLargest){
      lenLargest = intervalWidth;
      iLeftLargest = iLeft;
      iRightLargest = iRight;
    }
  }
  return (int)(iLeftLargest+lenLargest/2) % lenLargest;
}
