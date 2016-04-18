#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// Arduino pins

// Pins for IR
int irLEDPinLeft = 9;
int irRecPinLeft = 10;
int irLEDPinRight = 2;
int irRecPinRight = 3;

// Constants for IR
int irMaxFreq = 58000;
int irOptFreq = 38000;
int irFreqStep = 5000;
int nbrIRDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;

// Status LEDs
int statusLedPinLeft = 7;
int statusLedPinRight = 6;




#endif
