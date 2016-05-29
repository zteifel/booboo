#ifndef ONBLACKPAPER_H
#define ONBLACKPAPER_H

#include "Arduino.h"
#include "declarations.h"

bool onBlackPaper(){
  if (digitalRead(stopOnBlackPin) == LOW) {
    Serial.println("black one read");
    stopOnBlackCount++;
  }
  else {
    Serial.println("black reset");
    stopOnBlackCount = 0;
  }
  if (stopOnBlackCount >= stopOnBlackThreshold) {
    Serial.println("found black paper");
    stopOnBlackCount = 0;
    return true;
  }
  return false;
}

#endif
