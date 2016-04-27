#include "declarations.h"
#include <Servo.h>     

Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  //tone(4, 2000,500);
  //delay(1000);
  //tone(4, 2000, 500);

  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);

  servoLeft.attach(13);
  servoRight.attach(12);

}

void loop() {
  float irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  float irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  digitalWrite(statusLedPinLeft, LOW);
  digitalWrite(statusLedPinRight, LOW);
  
  
  if(irDistLeft < 0.8){
      digitalWrite(statusLedPinLeft, HIGH);
    }
  
  if(irDistRight < 0.8){
       digitalWrite(statusLedPinRight, HIGH); 
    }
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight); 

}

// IR distance measurement function
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

// IR Detection function
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);             // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}    
