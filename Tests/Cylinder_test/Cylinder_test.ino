
#include <Servo.h> // Include servo library
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "irDistance.h"
#include "Avoidance.h"

bool foundCylinder = false;

void setup() {

  Serial.begin(9600);

  servoLeft.attach(leftServoPin);
  servoRight.attach(rightServoPin);
  
  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);

  pinMode(GALV_PIN, INPUT);

}

void loop() {

  if (foundCylinder) {
    stopMovement();
  } else {
    galvReading = digitalRead(GALV_PIN);
    if (galvReading == HIGH) {
      foundCylinder = true;
    } else if (irDistLeft < 0.8) {
      turnLeft();
    } else if (irDistRight < 0.8) {
      turnRight();
    } else {
      moveForwardSlow();
    }
  }
  
  

}
