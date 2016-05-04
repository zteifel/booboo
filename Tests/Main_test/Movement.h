#include "Arduino.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H


void moveForward() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightForward);
}

void turnLeft() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightForward);
}

void turnRight() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void reverse() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void moveForwardSlow() {
    servoLeft.writeMicroseconds(servoLeftForwardSlow);
    servoRight.writeMicroseconds(servoRightForwardSlow);
}



#endif
