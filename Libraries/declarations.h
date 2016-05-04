#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// Arduino pins

// Pins for IR
const int irLEDPinLeft = 9;
const int irRecPinLeft = 10;
const int irLEDPinRight = 2;
const int irRecPinRight = 3;

// Constants for IR
const int irMaxFreq = 58000;
const int irOptFreq = 38000;
const int irFreqStep = 5000;
const int nbrIRDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;

// Constant for random seeding
//const int randomPin = A0;

// Pins for sonar
const int pingPin = 6;

// Buzzer pin
const int beepPin = 7;

#endif
