// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
    
Servo servoLeft;
Servo servoRight;

const int pingPin = 6;
const int beepPin = 7;
const int stepsInFullTurn = 38;
const int discardCylDist = 65;
const int horizonDist = 300;
const bool clockwise = true;
const bool counterClockwise = false;

long pingDist;
int  measurements[stepsInFullTurn];
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
  measure();
  tone(beepPin, 2000, 500);
  Serial.println(arrayToString(measurements,stepsInFullTurn));
  delay(1000);
  stepsToCylinder = findCylinder();
  Serial.println("Cylinder at index: "+String(stepsToCylinder));
  tone(beepPin, 2000, 500);
  for(int i=0; i<stepsInFullTurn-stepsToCylinder; i++){
    rotateStep(clockwise);
  }
  tone(beepPin, 5000, 500);
  while(measurePingDist()>10){
    moveForward();
  }
  delay(4000);
}

// Performs full turn and saves measurements to array
// Notes measurements that are too far to be a cylinder
void measure(){ 
  for(int i=0; i<stepsInFullTurn; i++){ 
    rotateStep(counterClockwise);
    int m = measurePingDist();
    
    Serial.println("Measured: "+String(m));
    measurements[i] = m;
    if(m > discardCylDist) // TODO Should be "m > discardCylDist"?
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
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);
  } else {
    servoLeft.writeMicroseconds(1400);
    servoRight.writeMicroseconds(1400);
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
void moveForward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
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
  const int l = stepsInFullTurn;

  while(true){
    int nearestIndex = getIndexMin();
    
    Serial.println("Nearest index found: "+String(nearestIndex));
    if(nearestIndex == -1){
      return getIndexOfLargestOpenInterval();
    }
    int iL = prevIndex(nearestIndex,l);
    int iR = nextIndex(nearestIndex,l);
    int intervalLength = 0;
  
    while(abs(measurements[nearestIndex] - measurements[iL]) < 5){
      iL = prevIndex(iL,l);
      intervalLength++;
    }
    while(abs(measurements[nearestIndex] - measurements[iR]) < 5){
      iR = nextIndex(iR,l);
      intervalLength++;
    }

    
    Serial.println("intervalLength: "+String(intervalLength));

    if(intervalLength <= 5){
      return iL<iR ? (iL + iR)/2 : ((iL + iR+l)/2)%l;
    } else {
      for(int i=iL; i<iR; i=nextIndex(i,l)){
        noCylinder[i] = true; 
      }
    }
  }
}
// Index of the closest measured distance
int getIndexMin(){
  int minVal = 500; //Max
  int iMinVal = -1;
  
  for(int i=0; i<stepsInFullTurn; i++){
    if( !noCylinder[i] && (measurements[i] < minVal) ){
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
  int nbrOfRightChecks = 0;
  //int startIndex = 0; // TODO This variable was unused
  

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


