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

// Pins for sonar
const int pingPin = 6;

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
const float irDistThreshold     = 0.5;

Servo servoLeft;
Servo servoRight;

// Other
int speakerPin = 7; // Status speaker, resistor?
int buttonPin = 8;  // Status speaker, resistor?

// Sonar
const int ultraSoundPin = 6;
const int discardCylDist = 65;
const int horizonDist = 100;
const int extraSwipeSteps = 3;
const int noCylFound = -1;
const int rotationSpeed = 25;
const int msInFullTurn = 8000;
const int nMeasurements = 50;
const int msPerStep = msInFullTurn / nMeasurements;
const bool clockwise        = true;
const bool counterClockwise = false;
int  measurements[nMeasurements];
int  noCylinder[nMeasurements];
int  stepsToCylinder;
int  targetWidth; // Special for profileScan


#endif
