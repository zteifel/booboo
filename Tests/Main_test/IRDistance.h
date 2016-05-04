
#include "Arduino.h"

#ifndef IRDISTANCE_H
#define IRDISTANCE_H

float irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  irDetected = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return irDetected;                                 // Return 1 no detect, 0 detect
}


float irDistance(int irLedPin, int irReceivePin)
{ 
  irSumDistZones = 0.0;
  for(int k = 1; k<= irNbrAvgRuns ; k++) { 
    irTmpDist = 0.0;
    for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
      irTmpDist += irDetect(irLedPin, irReceivePin, f);
    }
    irSumDistZones  += irTmpDist;
  }
  irMeanDistZone = irSumDistZones/irNbrAvgRuns;

  return irMeanDistZone/irNbrDistZones; // Normalize to 1
}


#endif
