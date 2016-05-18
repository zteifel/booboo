
#include "declarations.h"
#include "irDistance.h"

void setup() {

  pinMode(irRecPinLeft, INPUT);
  pinMode(irRecPinRight, INPUT); 
  pinMode(irLEDPinLeft, OUTPUT);
  pinMode(irLEDPinRight, OUTPUT);

  Serial.begin(9600);
  Serial.flush();

}

void loop() {

  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);

  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight);

}



