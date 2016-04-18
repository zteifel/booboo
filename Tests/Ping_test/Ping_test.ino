#include <Servo.h>          // Include servo library
    
Servo servoLeft;
Servo servoRight;

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 8;
long pingDist;
const int nMeasurements = 20;
int measurements[nMeasurements];
int nRotations = 0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  

  rotateStep(false);
  pingDist = measurePingDist();
  measurements[nRotations] = pingDist;
  Serial.println(String(measurements[nRotations]));
  ++nRotations %= nMeasurements;

  delay(100);
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
  cm = microsecondsToCentimeters(duration);

  //Serial.println(String(cm)+" cm");
  return cm;
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
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
void standStill() {
  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
