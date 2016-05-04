
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Servo.h>

const bool clockwise = true;
const bool counterClockwise = false;
const int stepsInFullTurn = 38;

void rotateStep(Servo servoLeft, Servo servoRight, bool clockwise);
void rotate(Servo servoLeft, Servo servoRight, bool clockwise, int speed);
void stopMovement(Servo servoLeft, Servo servoRight);
void moveForward(Servo servoLeft, Servo servoRight);
void moveALittleInRandDir(Servo servoLeft, Servo servoRight);
void moveALittleInDir(Servo servoLeft, Servo servoRight, int stepsToRotate, bool clockwise, int timeToMove);

#endif
