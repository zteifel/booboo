#include "Arduino.h"
#include <Servo.h> // Include servo library
#ifndef DECLARATIONS_H
#define DECLARATIONS_H


// Arduino pins

// Pins
// Digital
const int irRecPinLeft = 5;    // 200 ohm resistor
const int irRecPinRight = 4;  // 200 ohm resistor	
const int irLEDPinLeft = 3;   // 1.8k ohm resistor
const int irLEDPinRight = 2;  // 1.8k ohm resistor
const int pingPin = 6;	// Ultrasound
const int beepPin = 7;	// Buzzer
const int buttonPin = 8;  // Status speaker, resistor?
const int leftServoPin = 13;
const int rightServoPin = 12;

const int stopOnBlackPin = 9;

// Analogue
const int GALV_PIN = 10;
const int IR_BEACON_L_PIN  = A4;
const int IR_BEACON_R_PIN = A5;



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

// Sonar
const int discardCylDist = 65;
const int horizonDist = 100;
const int extraSwipeSteps = 3;
const int noCylFound = -1;
const int rotationSpeed = 25;
const int msInFullTurn = 8000;
const int nMeasurements = 50;
const int msPerStep = msInFullTurn / nMeasurements;
int  measurements[nMeasurements];
int  noCylinder[nMeasurements];
int  stepsToCylinder;

// Servo
const int servoOffset           = 4;
const int servoLeftForward      = 1600;
const int servoLeftBackward     = 1400;
const int servoRightForward     = 1400;
const int servoRightBackward    = 1600;
const int servoLeftForwardSlow  = 1530;
const int servoLeftBackwardSlow  = 1470;
const int servoRightForwardSlow = 1470;
const int servoRightBackwardSlow = 1530;
const int servoStop             = 1500;
const float irDistThreshold     = 0.6;

Servo servoLeft;
Servo servoRight;

// IR Beacon
const float analogConversionFactor = 5.0 / 1024.0;
const float beaonTimerTreshold = 2000;
float beaconLeftVal, beaconRightVal;
float curTime, beaconLeftTimer, beaconRightTimer;


// Other
const int msMoveForward = 10*1000; // TODO this number is untested
const int roamingTime = 3; // Seconds
int galvReading = 0;

const bool clockwise        = true;
const bool counterClockwise = false;

#endif
