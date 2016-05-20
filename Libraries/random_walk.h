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
    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);
    moveForward();
    avoidObjects(irDistLeft, irDistRight);
    delay(100);
  }
}


#endif
