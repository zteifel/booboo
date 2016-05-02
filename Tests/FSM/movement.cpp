
#include "movement.h"
#include <Servo.h>
#include "Arduino.h"

// Rotates one step clockwise or counter-clockwise
void rotateStep(Servo servoLeft, Servo servoRight, bool clockwise) {
  if(clockwise){
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1600);
  } else {
    servoLeft.writeMicroseconds(1400);
    servoRight.writeMicroseconds(1400);
  }
  delay(100);
  stopMovement(servoLeft, servoRight);
  delay(100);
}

// Halts robot
void stopMovement(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void moveForward(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}
