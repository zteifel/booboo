#ifndef CATCH_CYLINDER_H
#define CATCH_CYLINDER_H

#include "declarations.h"
#include "movement.h"
#include "irDistance.h"
#include "Arduino.h"
#include "avoidance_whiskers.h"

void catch_cylinder(){
  bool foundCylinder = false;

  while(true){

    if(millis() - time > msMoveTowardCylinder){
      currentState = STATE_PING_SCAN;
      Serial.println("Catch cylinder timed out");
      break;
    }

    if(digitalRead(stopOnBlackPin) == LOW){		// Do a random walk
      Serial.println("Trying to catch an already captured cylinder");
      reverse();	// Go backwards first
      delay(1000);
      randomWalk(0,50,5);  // Random dir in 5sec to get a new position
      currentState = STATE_PING_SCAN;  // Search for a new cylinder
      break;
    }

    galvReading = digitalRead(GALV_PIN);
    if (galvReading == HIGH) {
      stopMovement();

      delay(500);
      servoArm.write(armDown);
      Serial.println("Catched a cylinder");
      delay(500);

      currentState = STATE_MOVE_TO_BEACON;
      break;
    }

    if(avoidance_whiskers()) {
      currentState = STATE_MOVE_AND_AVOID;
      break;
    }

    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);

    if (irDistLeft < 1.1 && irDistRight < 1.1) {
      moveStraight(50);
    } else if (IRTurnCounter >= IRTurnCountThreshold) {
      moveStraight(50);
    } else if (irDistLeft < 0.8) {
      turnLeftSlow();
      IRTurnCounter++;
    } else if (irDistRight < 0.8) {
      turnRightSlow();
      IRTurnCounter++;
    } else {
      moveStraight(50);
      IRTurnCounter = 0;
    }

    delay(100);
  }
}

#endif
