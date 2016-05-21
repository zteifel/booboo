#include "Arduino.h"

#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

void randomDirection(int a, int b){
  // a, b is the direction index limits. Index 0 is straight ahead and index 50 is approx a full turn.
  stopMovement();
  int randomDir = random(a, b);  // Random dir backwards
  rotate(clockwise, rotationSpeed); // Rotate
  delay(msPerStep * randomDir);
}

void randomWalk(int a, int b, int walkTime) {		// Walktime in seconds
  stopMovement();
  randomDirection(a, b);  // Random 360 dirr
  for (int i = 1; i < walkTime*10; i++) {    
    
    moveForward();
    if(currentState == STATE_MOVE_TO_BEACON) {  // Already have a cylinder, avoiding with IR
      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      avoidObjects(irDistLeft, irDistRight);
    } else {  // Dont have a cylinder, avoiding with whiskers and checking if accidently hit a cylinder
      galvReading = digitalRead(GALV_PIN);
      avoidance_whiskers();
      if (galvReading == HIGH) {
          currentState = STATE_CATCH_CYLINDER;
          break;
      }
    }
    delay(100);
  }
}


#endif
