#include "Arduino.h"

#include <Servo.h> // Include servo library
#ifndef MOVEMENT_H
#define MOVEMENT_H


void moveForward() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightForward);
}

void stopMovement() {
    servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void turnLeft() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightForward);
}

void turnLeftSlow() {
  servoLeft.writeMicroseconds(servoLeftBackwardSlow);
  servoRight.writeMicroseconds(servoRightForwardSlow);
}


void turnRight() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void turnRightSlow() {
  servoLeft.writeMicroseconds(servoLeftForwardSlow);
  servoRight.writeMicroseconds(servoRightBackwardSlow);
}


void reverse() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void moveForwardSlow() {
    servoLeft.writeMicroseconds(servoLeftForwardSlow);
    servoRight.writeMicroseconds(servoRightForwardSlow);
}

// Rotates continually
// Note: a full turn is about 7 seconds with speed setting 25. (TODO double check this)
void rotate(bool clockwise, int speed){
  if(clockwise){
    servoLeft.writeMicroseconds(1500 + speed);
    servoRight.writeMicroseconds(1500 + speed);
  } else {
    servoLeft.writeMicroseconds(1500 - speed);
    servoRight.writeMicroseconds(1500 - speed);
  }
}

void moveStraight(int speed){
    servoLeft.writeMicroseconds(1500 + speed);
    servoRight.writeMicroseconds(1500 - speed);
}

#endif
