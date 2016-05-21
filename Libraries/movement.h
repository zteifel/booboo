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

void moveStraight(int speed){
    servoLeft.writeMicroseconds(1500 + speed);
    servoRight.writeMicroseconds(1500 - speed);
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

void rotateAroundBase(){
  // a, b is the direction index limits. Index 0 is straight ahead and index 50 is approx a full turn.
  reverse();    // Go backwards first
  delay(2500);
  rotate(clockwise, rotationSpeed);	// Rotate
  delay(msPerStep * 9); // Approx 45 degrees
  servoLeft.writeMicroseconds(1500 + 50);
  servoRight.writeMicroseconds(1500 - 100);
  delay(8000);
  rotate(clockwise, rotationSpeed);	// Rotate
  delay(msPerStep * 9); // Approx 45 degrees
  stopMovement();
}

#endif
