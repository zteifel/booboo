#ifndef DELAYFUNCTIONS_H
#define DELAYFUNCTIONS_H

#include "Arduino.h"

void delayWithIRAvoidance(int delayTime) {
  unsigned long begin = millis();
  while (millis() - begin < delayTime) {
    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);
    avoidObjects(irDistLeft, irDistRight);
    delay(100);
  }
}

void delayWithWhiskerAvoidance(int delayTime) {
  unsigned long begin = millis();
  while (millis() - begin < delayTime) {
    avoidance_whiskers();
    delay(50);
  }
}
#endif
