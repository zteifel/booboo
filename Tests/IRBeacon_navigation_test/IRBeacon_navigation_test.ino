#include <Servo.h>

const int IR_BEACON_L_PIN  = A0;
const int IR_BEACON_R_PIN = A1;
const int SERVO_L_PIN = 13;
const int SERVO_R_PIN = 12;

// Constants for servo
Servo servoRight;
Servo servoLeft;
int servoLeftForward = 1550;
int servoLeftBackward = 1450;
int servoRightForward = 1450;
int servoRightBackward = 1550;

const float analogConversionFactor = 5.0 / 1024.0;
float irBeaconLeftVal, irBeaconRightVal, tmpSum, irBeaconMeanValue;
float leftSum, rightSum;
void setup() {
  Serial.begin(9600);
  pinMode(IR_BEACON_L_PIN, INPUT);
  pinMode(IR_BEACON_R_PIN,INPUT);
  servoLeft.attach(SERVO_L_PIN);
  servoRight.attach(SERVO_R_PIN);

  leftSum = rightSum = 0;
}

void loop() {
  irBeaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
  irBeaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;

  if(irBeaconLeftVal == 0 && irBeaconRightVal > 0) {
    leftSum++;
  } else if(irBeaconRightVal == 0 && irBeaconLeftVal > 0) {
    rightSum++;
  } else if(irBeaconRightVal == 0 && irBeaconLeftVal == 0){
    leftSum = rightSum = 0;
  }
  
  if(leftSum < rightSum){
    turnRight(servoLeft,servoRight);
  } else if (leftSum > rightSum){
    turnLeft(servoLeft,servoRight);
  } else { //leftSum == rightSum
    moveForward(servoLeft,servoRight);
  } 
  delay(100);
}

void turnLeft(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoRightBackward);
  servoRight.writeMicroseconds(servoLeftForward);
}
void turnRight(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightForward);
}
void moveForward(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightForward);
}

