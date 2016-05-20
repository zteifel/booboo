#include "Arduino.h"
#include <Servo.h> // Include servo library
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// States
const int STATE_MOVE_AND_AVOID  = 0;
const int STATE_PING_SCAN       = 1;
const int STATE_CATCH_CYLINDER  = 2;
const int STATE_MOVE_TO_BEACON  = 3;
const int STATE_DROP_CYLINDER   = 4;
int currentState;

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
const int ARM_SERVO_PIN = 11;
const int stopOnBlackPin = 9;

// Analogue
const int GALV_PIN = A1;
const int WHISKER_L_PIN  = A2;
const int WHISKER_R_PIN = A3;
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
/*
const int discardCylDist = 65;
const int horizonDist = 100;
const int extraSwipeSteps = 3;
const int noCylFound = -1;
int  noCylinder[nMeasurements];
int  stepsToCylinder;
const int msInFullTurn = 8500;
const int msPerStep = msInFullTurn / nMeasurements;
*/
const int rotationSpeed = 25;
const int msPerStep = 8500/50; // Gamla msInFullTurn / nMeasurements == 8500/50
const int nMeasurements = 50;
const int maxCylWidth = 7;
const int minCylDepth = 5;
const int maxCylDist = 60;
const int timeOut_ping = 10*1000;
int  measurements[nMeasurements];

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
Servo servoArm;

// IR Beacon
const float analogConversionFactor = 5.0 / 1024.0;
const float beaonTimerTreshold = 2000;
float beaconLeftVal, beaconRightVal;
float curTime, beaconLeftTimer, beaconRightTimer;


// Other
unsigned long time;

const int msMoveTowardCylinder = 10*1000;
const int roamingTime = 1.5; // Seconds

int galvReading = 0;

const bool clockwise        = true;
const bool counterClockwise = false;

const int armUp = 90;
const int armDown = 30;

int leftWhiskerReading, rightWhiskerReading;

int IRTurnCounter = 0;
int IRTurnCountThreshold = 6;

#endif
