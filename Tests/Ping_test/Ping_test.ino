// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
    
Servo servoLeft;
Servo servoRight;

const int pingPin = 8;

long      pingDist;
const int nMeasurements = 20;
int       measurements[nMeasurements];
int       measureIndex = 0;
const int STATE_SEARCH    = 0;
const int STATE_APPROACH  = 1;
const int STATE_FOUND     = 2;
int       currentState = STATE_SEARCH;

const bool clockwise = true;
const bool counterClockwise = false;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
 
  pingDist = measurePingDist();
  measurements[measureIndex] = pingDist;
  Serial.println(arrayToString(measurements,nMeasurements));

  switch (currentState) {
    case STATE_SEARCH:
      rotateStep(counterClockwise);
      if((measurements[measureIndex]<100) &&
         (measurements[measureIndex] < getMeanMeasurement(4)*0.66)
        ){
        stopMovement();
        tone(4, 5000, 500);
        delay(1000);
        tone(4, 4000, 500);
        currentState = STATE_APPROACH;
      }
      delay(100);
      break;
    case STATE_APPROACH:
      if(measurements[measureIndex]<10){
        currentState = STATE_FOUND;
        stopMovement();
      } else { 
        moveForward();
      }
      break;
    case STATE_FOUND:
      stopMovement();
      if(measurements[measureIndex]>10){
        currentState = STATE_SEARCH;
      }
      break;
  }
  //Loop around to 0 before out of bounds:
  ++measureIndex %= nMeasurements;
}

long getMeanMeasurement(int n){
  long sum = 0;
  for(int i=1; i<=n; i++){
    int arrayIndex = (measureIndex - i + nMeasurements) % nMeasurements;
    sum += measurements[arrayIndex];
  }
  return (sum/n)+0.5;
}

String arrayToString(int array[], int arrayLength)
{
  String s = "[ ";
  for(int i=0; i < arrayLength; i++){
    s+=String(array[i])+" ";
  }
  return s + "]";
}
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

void rotateStep(bool clockwise) {
  if(clockwise){
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
  } else {
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
  }
  delay(50);
  stopMovement();
}

void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void moveForward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
