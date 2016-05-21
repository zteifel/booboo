#include <Servo.h> // Include servo library
#include <EEPROM.h>
#include "declarations.h"
#include "irDistance.h"
#include "movement.h"
#include "beeps.h"
#include "Avoidance.h"
#include "avoidance_whiskers.h"
#include "random_walk.h"
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

  pinMode(WHISKER_L_PIN, INPUT);
  pinMode(WHISKER_R_PIN, INPUT);

  servoArm.attach(ARM_SERVO_PIN);

  Serial.flush();

  servoArm.write(armUp); // Set the arm in diagonal upright position

  currentState = STATE_MOVE_AND_AVOID;

}

void loop() {
  Serial.println(currentState); // DEBUG

  startTime = millis();

  if (currentState == STATE_MOVE_AND_AVOID) {
    // State 0: Move forward a set number of steps and then go to state 1. Avoid any objects.    

    randomWalk(0,50,3);  // Go a random dir during 3 sec

    currentState = STATE_PING_SCAN;
    
  } else if (currentState == STATE_PING_SCAN) {
    // State 1: Use the sonar to search and find direction to a cylinder.
    time = millis();
    while(true){
      ping_scan();
      if(currentState != STATE_PING_SCAN)
        break;
    }
  
  } else if (currentState == STATE_CATCH_CYLINDER) {
    // State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
    time = millis();
    catch_cylinder();

  } else if (currentState == STATE_MOVE_TO_BEACON) {
    // Go towards beacon
    moveToBeacon();

  } else if (currentState == STATE_DROP_CYLINDER) {
    // Leave cylinder
    stopMovement();
    delay(500);
    servoArm.write(armUp);
    delay(500);

    beep3();  // Beep if dropped of a cylinder at base

    // Start a new roam in a random direction
    int moveAroundBase = random(0,2);
    if ( startTime > timeBeforeMoveAround && moveAroundBase > 0 ) {
      rotateAroundBase();
    } else {
      reverseAndRandomDir(13, 37);
    }
    currentState = STATE_MOVE_AND_AVOID;
  }

}
