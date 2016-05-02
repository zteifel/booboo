
#include "movement.h"
#include "declarations.h"
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

void moveALittleInRandDir(Servo servoLeft, Servo servoRight){
  randomSeed(analogRead(A0));
  int r = random(stepsInFullTurn/2);
  
  randomSeed(analogRead(A0));
  bool dir = (random()%2);
  while(r--){
    rotateStep(servoLeft,servoRight,dir);
  }
  moveForward(servoLeft, servoRight);
  delay(2000);
  stopMovement(servoLeft, servoRight);
}

