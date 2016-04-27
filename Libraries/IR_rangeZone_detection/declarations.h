#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// Arduino pins

// Pins for IR
int irRecPinLeft = 2;		// 200 ohm resistor
int irRecPinRight = 3;	// 200 ohm resistor
int irLEDPinLeft = 4;		// 1.8k ohm resistor
int irLEDPinRight = 5;	// 1.8k ohm resistor


// Other
int speakerPin = 9;	// Status speaker, resistor?
int buttonPin = 10;	// Status speaker, resistor?
int ultraSoundPin = 6;


// Constants for IR
int irMaxFreq = 58000;
int irOptFreq = 38000;
int irFreqStep = 5000;
int nbrIRDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;
float irNbrAvgRuns = 5.0;
float irMeanDistZone;
float irSumDistZones = 0.0;
float irTmpDist;
float irDetected;

#endif
