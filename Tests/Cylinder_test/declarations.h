#include "Arduino.h"
#include <Servo.h> // Include servo library
#ifndef DECLARATIONS_H
#define DECLARATIONS_H


// Arduino pins

// Pins for IR
int irRecPinLeft = 5;    // 200 ohm resistor
int irRecPinRight = 4;  // 200 ohm resistor
int irLEDPinLeft = 3;   // 1.8k ohm resistor
int irLEDPinRight = 2;  // 1.8k ohm resistor

// Constants for IR
const int irMaxFreq = 58000;
const int irOptFreq = 38000;
const int irFreqStep = 5000;
float irNbrDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;
float irNbrAvgRuns = 5.0;
float irMeanDistZone;
float irSumDistZones = 0.0;
float irTmpDist;
float irDistLeft, irDistRight;
float irDetected;

// Pins for servos
const int leftServoPin = 13;
const int rightServoPin = 12;

// Pins for sonar
const int pingPin = 6;
const int discardCylDist = 65;
const int horizonDist = 100;
const int extraSwipeSteps = 3;
const int noCylFound = -1;
const int rotationSpeed = 25;
const int msInFullTurn = 8000;
const int nMeasurements = 30;
const int msPerStep = msInFullTurn / nMeasurements;
int  measurements[nMeasurements];
int  noCylinder[nMeasurements];
int  stepsToCylinder;

// Buzzer pin
const int beepPin = 7;

// Servo
const int servoOffset           = 4;
const int servoLeftForward      = 1600;
const int servoLeftBackward     = 1400;
const int servoRightForward     = 1400;
const int servoRightBackward    = 1600;
const int servoLeftForwardSlow  = 1530;
const int servoRightForwardSlow = 1470;
const int servoStop             = 1500;
const float irDistThreshold     = 0.6;

Servo servoLeft;
Servo servoRight;

// Other
int buttonPin = 8;  // Status speaker, resistor?
const int GALV_PIN = 10;
int galvReading = 0;
int roamingTime = 3; // Seconds

bool clockwise        = true;
bool counterClockwise = false;


#endif