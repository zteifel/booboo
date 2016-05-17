
#include <Servo.h> // Include servo library
#include <EEPROM.h>
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "ping_analyze_scan.h"
#include "irDistance.h"
#include "Avoidance.h"
#include "IR_beacon_nav.h"
#include "onBlackPaper.h"
#include "ping_scan.h"

void setup() {

  Serial.begin(9600);

  servoLeft.attach(leftServoPin);
  servoRight.attach(rightServoPin);
  
  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
  
  pinMode(IR_BEACON_L_PIN, INPUT);
  pinMode(IR_BEACON_R_PIN,INPUT);
  
  pinMode(GALV_PIN, INPUT);
  pinMode(stopOnBlackPin, INPUT);
  
  servoArm.attach(ARM_SERVO_PIN);

  Serial.flush();

  servoArm.write(armUp); // Set the arm in diagonal upright position
  
  currentState = 2;

}

void loop() {
  Serial.println(currentState); // DEBUG
  
  // MEASURE DATA
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  
  if (currentState == 0) {
    // State 0: Move forward a set number of steps and then go to state 1. Avoid any objects.

    for (int i = 1; i < roamingTime*20; i++) {
      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      moveForward();
      avoidObjects(irDistLeft, irDistRight);
      delay(50);
    }

    currentState = 1;
    
  } else if (currentState == 1) {
    // State 1: Use the sonar to search and find direction to a cylinder.
    ping_scan();
  
  } else if (currentState == 2) {
    // State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
    time = millis();
    foundCylinder = false;
    
    while(true){
    
      if(millis() - time > msMoveTowardCylinder){
        currentState = 1;
        break;
      }

      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      
      if (foundCylinder) {
        stopMovement();
        currentState = 3;
        break;
      } else {
        galvReading = digitalRead(GALV_PIN);
        galvReading = LOW;
        if (galvReading == HIGH) {
          foundCylinder = true;
        } else if (irDistLeft < 0.8) {
          turnLeft();
        } else if (irDistRight < 0.8) {
          turnRight();
        } else {
          moveStraight(50);
        }
      }
    }
    
  } else if (currentState == 3) {
    // Collect cylinder
    stopMovement();
    delay(500);
    servoArm.write(armDown);
    delay(500);
    
    currentState = 4;
  } else if (currentState == 4) {
    // Go towards beacon

    steerTowardsBeacon();
    Serial.println("Beacon loop");
    
    while(!onBlackPaper()) {
      avoidObjects(irDistLeft,irDistRight);
      checkForBeacon(100);
      steerTowardsBeacon();
    }
    Serial.println("Stopped on black");
    currentState = 5;
    
  } else if (currentState == 5) {
    // Leave cylinder
    stopMovement();
    delay(500);
    servoArm.write(armUp);
    delay(2000);
    currentState = 4;  // For now
  }
}
