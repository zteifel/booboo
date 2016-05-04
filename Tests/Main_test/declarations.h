#include "Arduino.h"

#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// Pins for IR
int irRecPinLeft = 5;    // 200 ohm resistor
int irRecPinRight = 4;  // 200 ohm resistor
int irLEDPinLeft = 3;   // 1.8k ohm resistor
int irLEDPinRight = 2;  // 1.8k ohm resistor


// Other
int speakerPin = 7; // Status speaker, resistor?
int buttonPin = 8;  // Status speaker, resistor?
int ultraSoundPin = 6;


// Constants for IR
int irMaxFreq = 58000;
int irOptFreq = 38000;
int irFreqStep = 5000;
float irNbrDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;
float irNbrAvgRuns = 5.0;
float irMeanDistZone;
float irSumDistZones = 0.0;
float irTmpDist;
float irDistLeft, irDistRight;
float irDetected;

const int servoOffset = 4;
const int servoLeftForward = 1600;
const int servoLeftBackward = 1400;
const int servoRightForward = 1400;
const int servoRightBackward = 1600;
const int servoLeftForwardSlow = 1530;
const int servoRightForwardSlow = 1470;
const float irDistThreshold = 0.5;

Servo servoLeft;
Servo servoRight;

#endif
