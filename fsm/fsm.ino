
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
#include "ping_scan.h"
#include "catch_cylinder.h"

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
  
  currentState = STATE_CATCH_CYLINDER;

}

void loop() {


  // Serial.println(currentState); // DEBUG
  
  // MEASURE DATA
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  
  if (currentState == STATE_MOVE_AND_AVOID) {
    // State 0: Move forward a set number of steps and then go to state 1. Avoid any objects.

    for (int i = 1; i < roamingTime*20; i++) {
      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      moveForward();
      avoidObjects(irDistLeft, irDistRight);
      delay(50);
    }

    currentState = STATE_PING_SCAN;
    
  } else if (currentState == STATE_PING_SCAN) {
    // State 1: Use the sonar to search and find direction to a cylinder.
    ping_scan();
  
  } else if (currentState == STATE_CATCH_CYLINDER) {
    // State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
    catch_cylinder();
    
  } else if (currentState == STATE_MOVE_TO_BEACON) {
    // Go towards beacon

    steerTowardsBeacon();
    Serial.println("Beacon loop");
    
    while(digitalRead(stopOnBlackPin) == HIGH){ // Note: the onBlackPaper function didn't work for some reason.
      avoidObjects(irDistLeft,irDistRight);
      checkForBeacon(100);
      steerTowardsBeacon();
    }
    Serial.println("Stopped on black");
    currentState = STATE_DROP_CYLINDER;
    
  } else if (currentState == STATE_DROP_CYLINDER) {
    // Leave cylinder
    stopMovement();
    delay(500);
    servoArm.write(armUp);
    delay(2000);
  }
  
}
