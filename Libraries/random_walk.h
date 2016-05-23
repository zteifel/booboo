#include "Arduino.h"

#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

void randomDirection(int a, int b){
  // a, b is the direction index limits. Index 0 is straight ahead and index 50 is approx a full turn.
  stopMovement();
  int randomDir = random(a, b);  // Random dir backwards
  if(randomDir <= 25) {
    rotate(clockwise, rotationSpeed);
    delayWithWhiskerAvoidance(msPerStep * randomDir);
  } else {
    rotate(counterClockwise, rotationSpeed);
    delayWithWhiskerAvoidance(msPerStep * (50-randomDir));
  }
}

// Not sure if this is used anymore?
void reverseAndRandomDir(int a, int b){
  // a, b is the direction index limits. Index 0 is straight ahead and index 50 is approx a full turn.
  reverse();	// Go backwards first
  delay(1000);
  randomDirection(a, b);
  stopMovement();
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
      //avoidance_whiskers();

      if(digitalRead(stopOnBlackPin) == LOW) {  // Drop cylinder if accidently go over black
        currentState = STATE_DROP_CYLINDER;
        break;
      }

    } else {  // Dont have a cylinder, avoiding with whiskers and checking if accidently hit a cylinder

      galvReading = digitalRead(GALV_PIN);
      if (galvReading == HIGH) {
          Serial.println("galvad");
          currentState = STATE_CATCH_CYLINDER;
          break;
      }

      if (avoidance_whiskers()) {
        avoidedWallTimer = millis();
      }
/*

      if (millis() - avoidedWallTimer > avoidedWallTimerThreshold) {
        
        // Check for cylinders close by
        irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
        irDistRight = irDistance(irLEDPinRight, irRecPinRight);

        if (irDistLeft < 0.6) {
          Serial.println("ir left");
          ping_scan_rotate_dir = counterClockwise;
          currentState = STATE_PING_SCAN;
          break;
        }
        else if (irDistRight < 0.6) {
          Serial.println("ir right");
          ping_scan_rotate_dir = clockwise;
          currentState = STATE_PING_SCAN;
          break;
        }
      }*/
    }
    delay(100);
  }
}


#endif
