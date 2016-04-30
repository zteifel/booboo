
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Servo.h>

const bool clockwise = true;
const bool counterClockwise = false;
const int stepsInFullTurn = 38;

void rotateStep(Servo servoLeft, Servo servoRight, bool clockwise);
void stopMovement(Servo servoLeft, Servo servoRight);
void moveForward(Servo servoLeft, Servo servoRight);

#endif
