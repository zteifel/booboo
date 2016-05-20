#include "Arduino.h"

#ifndef AVOIDANCE_WHISKERS_H
#define AVOIDANCE_WHISKERS_H

bool avoidance_whiskers() {

  leftWhiskerReading = digitalRead(WHISKER_L_PIN);
  rightWhiskerReading = digitalRead(WHISKER_R_PIN);
  
  if (leftWhiskerReading == HIGH && rightWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnLeftSlow();
    delay(2000);
    return true;
  } else if (leftWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnRightSlow();
    delay(1300);
    return true;
  } else if (rightWhiskerReading == HIGH) {
    reverse();
    delay(500);
    turnLeftSlow();
    delay(1300);
    return true;
  } else {
    return false;
  }
}

#endif
