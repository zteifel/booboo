
#include <Servo.h>

#include "declarations.h"
#include "Movement.h"
#include "Avoidance.h"
#include "IRDistance.h"


void setup() {
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!");

  servoLeft.attach(13);
  servoRight.attach(12);

  Serial.flush();
  
  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
  

}

void loop() {
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);

  avoidObjects(irDistLeft, irDistRight);

}
