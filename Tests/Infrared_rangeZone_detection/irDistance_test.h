#ifndef IRDISTANCE_H
#define IRDISTANCE_H
#include "Arduino.h"

// IR Detection function

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED active for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver
  delay(1);                                  // Down time
  return ir;                                 // Return 1
}    


float irDistance(int irLedPin, int irReceivePin)
{ 
  float nbrAvgIrRuns = 5.0;
  float meanDistZone;
  float sumDistZones = 0.0;
  
  for(int k = 1; k<= nbrAvgIrRuns; k++) { 
    float distance = 0.0;
    for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
      distance += irDetect(irLedPin, irReceivePin, f);
    }
    sumDistZones += distance;
  }
  meanDistZone = sumDistZones/nbrAvgIrRuns;

  return meanDistZone/nbrIRDistZones; // Normalize to 1
}

#endif
