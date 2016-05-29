#include <Servo.h> // Include servo library
#include <EEPROM.h>
#include "declarations.h"
#include "onBlackPaper.h"
#include "irDistance.h"
#include "movement.h"
#include "beeps.h"
#include "Avoidance.h"
#include "avoidance_whiskers.h"
#include "delayFunctions.h"
#include "random_walk.h"
#include "IR_beacon_nav.h"
#include "ping_scan2.h"
#include "catch_cylinder.h"

// NYA

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

  servoArm.write(armUp); // Set the arm in upright position

  currentState = STATE_MOVE_AND_AVOID;
  
  startTime = millis();

}

void loop() {
  Serial.println(currentState); // DEBUG
  
  if (currentState == STATE_MOVE_AND_AVOID) {

    Serial.println("State: Move and avoid");
    
    currentState = STATE_PING_SCAN;
    randomWalk(0,0,6);  // Go forward dir during 3 sec
    
  } else if (currentState == STATE_PING_SCAN) {

    Serial.println("State: ping scan");

    
    time = millis();
    while(true){
      ping_scan();
      if(currentState != STATE_PING_SCAN)
        break;
    }
    
  } else if (currentState == STATE_CATCH_CYLINDER) {

    Serial.println("State: catch cylinder");
    
    time = millis();
    catch_cylinder();
    
  } else if (currentState == STATE_MOVE_TO_BEACON) {

    Serial.println("State: move to beacon");
    
    moveToBeacon();

  } else if (currentState == STATE_DROP_CYLINDER) {

    Serial.println("State: drop cylinder");
    
    // Leave cylinder
    stopMovement();
    delay(500);
    servoArm.write(armUp);
    delay(500);
    
    beep();  // Beep if dropped of a cylinder at base
    
    // Start a new roam in a random direction
    //int moveAroundBase = random(0,2);
    //if ( startTime > timeBeforeMoveAround && moveAroundBase > 0 ) {
    if (hasChangedSideCount < 2) {
      reverseAndRandomDir(20, 30);
      hasChangedSideCount++;
      //hasChangedSide = false;
    } else {
      //hasChangedSide = true;
      hasChangedSideCount = 0;
      rotateAroundBase();
    }
    //rotateAroundBase();
    currentState = STATE_MOVE_AND_AVOID;
  }

}
