#ifndef CATCH_CYLINDER_H
#define CATCH_CYLINDER_H

#include "declarations.h"
#include "movement.h"
#include "irDistance.h"
#include "Arduino.h"
#include "avoidance_whiskers.h"

// State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
void catch_cylinder(){
  bool foundCylinder = false;
    
  while(true){
  
    if(millis() - time > msMoveTowardCylinder){
      currentState = STATE_PING_SCAN;
      Serial.println("Catch cylinder time out.");
      break;
    }

    if(digitalRead(stopOnBlackPin) == LOW){		// Do a random walk
      Serial.println("Trying to catch an already captured cylinder");
      reverseAndRandomDir(13, 37);
      currentState = STATE_MOVE_AND_AVOID;
      break;
    }

    
    if (foundCylinder) {
      
      stopMovement();
      currentState = STATE_MOVE_TO_BEACON;
      
      delay(500);
      servoArm.write(armDown);
      delay(500);
      
      break;
      
    } else {
      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      galvReading = digitalRead(GALV_PIN);

      if (galvReading == HIGH) {
        foundCylinder = true;
      } else {
        if(avoidance_whiskers()) {
          currentState = STATE_MOVE_AND_AVOID;
          break;
        }
        if (irDistLeft < 0.95 && irDistRight < 0.95) {
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
      }
      delay(100);
    }
  }
  
}

#endif
