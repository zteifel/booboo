#include "Arduino.h"
#include "IR_rangeZone_detection.h"
#include "declarations.h"


IR_rangeZone_detection::IR_rangeZone_detection()
{
  tone(speakerPin, 2000,500);
  delay(1000);
  tone(speakerPin, 2000, 500);
  
  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
}

float IR_rangeZone_detection::irDistance(int irLedPin, int irReceivePin)
{
  float irSumDistZones = 0.0;
  for(int k = 1; k<= irNbrAvgRuns ; k++) { 
    irTmpDist = 0.0;
    for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
      irTmpDist += irDetect(irLedPin, irReceivePin, f);
    }
    irSumDistZones  += irTmpDist;
  }
  float irMeanDistZone = irSumDistZones/irNbrAvgRuns ;

  return irMeanDistZone/irNbrAvgRuns ; // Normalize to 1
}

float IR_rangeZone_detection::irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  irDetected = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return irDetected;                                 // Return 1 no detect, 0 detect
}

float IR_rangeZone_detection::getLeftDistance()
{
  return irDistance(irLEDPinLeft, irRecPinLeft);
}

float IR_rangeZone_detection::getRightDistance()
{
  return irDistance(irLEDPinRight, irRecPinRight);
}

