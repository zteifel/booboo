#ifndef CATCH_CYLINDER_H
#define CATCH_CYLINDER_H

#include "declarations.h"
#include "movement.h"
#include "irDistance.h"

// State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
void catch_cylinder(){
  unsigned long time = millis();
  bool foundCylinder = false;
    
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
        foundCylinder = true; // DEBUG
      } else if (irDistLeft < 0.8) {
        turnLeft();
      } else if (irDistRight < 0.8) {
        turnRight();
      } else {
        moveStraight(50);
      }
    }
  }
  
}

#endif
