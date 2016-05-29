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
// Note: a full turn is about 8 seconds with speed setting 25.
void rotate(bool clockwise, int speed){
  if(clockwise){
    servoLeft.writeMicroseconds(1500 + speed);
    servoRight.writeMicroseconds(1500 + speed);
  } else {
    servoLeft.writeMicroseconds(1500 - speed);
    servoRight.writeMicroseconds(1500 - speed);
  }
}

bool avoidObjectsTemp(float irDistLeft, float irDistRight) {


  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
    Serial.println("IR Avoidance: Reversing");
    Serial.print(irDistLeft);
    Serial.print("  ");
    Serial.println(irDistRight);
    return true;
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    //Serial.println("Right");
    return true;
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    //Serial.println("Left");
    return true;
  } else {
    return false;
  }
}

bool delayWithIRAvoidanceTemp(int delayTime) {
  unsigned long begin = millis();
  while (millis() - begin < delayTime) {
    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);
    if(!avoidObjectsTemp(irDistLeft, irDistRight)){
      servoLeft.writeMicroseconds(1500 + 55);
      servoRight.writeMicroseconds(1500 - 100);
    }
    delay(100);
  }
}

void rotateAroundBase(){
  reverse();    // Go backwards first
  delay(2500);
  rotate(clockwise, rotationSpeed);	// Rotate
  delay(msPerStep * 9); // Approx 45 degrees
  servoLeft.writeMicroseconds(1500 + 55);
  servoRight.writeMicroseconds(1500 - 100);
  delayWithIRAvoidanceTemp(8000);
  rotate(clockwise, rotationSpeed);	// Rotate
  delay(msPerStep * 9); // Approx 45 degrees
  stopMovement();
}



#endif
