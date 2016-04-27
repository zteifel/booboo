#include "declarations.h"
//#include "irDistance.h"

void setup()                                 // Built-in initialization block
{
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  //tone(speakerPin, 2000,500);
  //delay(1000);
  //tone(speakerPin, 2000, 500);

  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
}  
 
void loop()                                  // Main loop auto-repeats
{
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight);

}

// IR distance measurement function

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
  irMeanDistZone = irSumDistZones/irNbrAvgRuns ;

  return irMeanDistZone/irNbrAvgRuns ; // Normalize to 1
}

// IR Detection function

float irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  irDetected = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return irDetected;                                 // Return 1 no detect, 0 detect
}    
