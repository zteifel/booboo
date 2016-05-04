
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

// Rotates continually
// Note: a full turn is about 7 seconds with speed setting 25. (TODO double check this)
void rotate(Servo servoLeft, Servo servoRight, bool clockwise, int speed){
  if(clockwise){
    servoLeft.writeMicroseconds(1500 + speed);
    servoRight.writeMicroseconds(1500  + speed);
  } else {
    servoLeft.writeMicroseconds(1500 - speed);
    servoRight.writeMicroseconds(1500 - speed);
  }
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

  moveALittleInDir(servoLeft,servoRight,r,dir,2000);
}

void moveALittleInDir(Servo servoLeft, Servo servoRight, int stepsToRotate, bool clockwise, int timeToMove){
  while(stepsToRotate--){
    rotateStep(servoLeft,servoRight,clockwise);
  }
  moveForward(servoLeft, servoRight);
  delay(timeToMove);
  stopMovement(servoLeft, servoRight);
}

