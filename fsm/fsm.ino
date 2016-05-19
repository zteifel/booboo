
#include <Servo.h> // Include servo library
#include <EEPROM.h>
#include "declarations.h"
#include "movement.h"
#include "beeps.h"
#include "irDistance.h"
#include "Avoidance.h"
#include "IR_beacon_nav.h"
#include "ping_scan2.h"
#include "catch_cylinder.h"

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(0));
  
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
  
  currentState = STATE_MOVE_AND_AVOID;

}

void loop() {


  // Serial.println(currentState); // DEBUG
  
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
    time = millis();
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
      //avoidObjects(irDistLeft,irDistRight);
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
    delay(500);
    
    beep();
    
    // Start a new roam in a random direction
    reverse();
    delay(1000);
    stopMovement();
    int randomDir = random(13, 37);
    rotate(clockwise, rotationSpeed);
    delay(msPerStep * randomDir);
    stopMovement();
    currentState = STATE_MOVE_AND_AVOID;
  }
  
}
