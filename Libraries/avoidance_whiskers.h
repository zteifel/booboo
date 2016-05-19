#include "Arduino.h"

#ifndef AVOIDANCE_WHISKERS_H
#define AVOIDANCE_WHISKERS_H

void avoidance_whiskers() {

  leftWhiskerReading = digitalRead(WHISKER_L_PIN);
  rightWhiskerReading = digitalRead(WHISKER_R_PIN);
  
  if (leftWhiskerReading == HIGH && rightWhiskerReading == HIGH) {
    reverse();
    delay(1500);
    turnLeft();
    delay(3000);
  } else if (leftWhiskerReading == HIGH) {
    reverse();
    delay(1500);
    turnRight();
    delay(2000);
  } else if (rightWhiskerReading == HIGH) {
    reverse();
    delay(1500);
    turnLeft();
    delay(2000);
  }
}

#endif
