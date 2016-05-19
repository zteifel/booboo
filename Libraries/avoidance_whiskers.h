#include "Arduino.h"

#ifndef AVOIDANCE_WHISKERS_H
#define AVOIDANCE_WHISKERS_H

bool avoidance_whiskers() {

  leftWhiskerReading = digitalRead(WHISKER_L_PIN);
  rightWhiskerReading = digitalRead(WHISKER_R_PIN);
  
  if (leftWhiskerReading == HIGH && rightWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnLeft();
    delay(3000);
    return true;
  } else if (leftWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnRightSlow();
    delay(1500);
    return true;
  } else if (rightWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnLeftSlow();
    delay(1500);
    return true;
  } else {
    return false;
  }
}

#endif
