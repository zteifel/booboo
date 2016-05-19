#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Arduino.h"
#include <Servo.h> // Include servo library
#include "declarations.h"

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

void reverseAndRandomDir(int a, int b){
  // a, b is the direction index limits. Index 0 is straight ahead and index 50 is approx a full turn.
  reverse();	// Go backwards first
  delay(1000);
  int randomDir = random(a, b);	// Random dir backwards
  rotate(clockwise, rotationSpeed);	// Rotate
  delay(msPerStep * randomDir);
  stopMovement();
}

#endif
