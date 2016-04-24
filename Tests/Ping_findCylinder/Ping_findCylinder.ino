// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
    
Servo servoLeft;
Servo servoRight;

const int pingPin = 8;
const int stepsInFullTurn = 25;

long      pingDist;
int       measurements[stepsInFullTurn];

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

void measure(){ 
  for(int i=0; i<stepsInFullTurn; i++){ 
    rotateStep(counterClockwise);
    measurements[i] = measurePingDist(); 
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
  delay(100);
  stopMovement();
  delay(100);
}

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

int prevIndex(int index, int arrayLength){
  return (index+arrayLength-1) % arrayLength;
}
int nextIndex(int index, int arrayLength){
  return (index+1) % arrayLength;
}
int findCylinder(){
  //stepsInFullTurn;
  //measurements;
  const int l = stepsInFullTurn;

  
  int noCylLen = 0; 
  int noCyl[noCylLen];

  while(1){
    int nearestIndex = getIndexMin(measurements, l, noCyl, noCylLen);
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
        //noCylLen += intervalLength;
        const int noCylLenNew = noCylLen + intervalLength;
        int noCylNew[noCylLenNew];
        for(int i=0; i<noCylLen; i++){
          noCylNew[i]=noCyl[i];
        }
        for(int i=noCylLen; i<noCylLenNew; i++){
          noCylNew[i] = measurements[iL + i];
        }
        noCyl = noCylNew;      
    }
  }
}

int getIndexMin(int a[], int aLen, int noCyl[], int noCylLen){
  int m = 0;
  while(contains(noCyl,noCylLen,a[m++]))
    ;
  
  for(int i=0; i<aLen; i++){
    if( (noCylLen && !contains(noCyl,noCylLen,a[i])) &&
        (a[m] > a[i]) ){
      m = i;
    }
  }
  return m;
}

bool contains(int a[], int aLen, int e){
  for(int i=0; i<aLen; i++){
    if(a[i] == e)
      return true;
  }
  return false;
}

