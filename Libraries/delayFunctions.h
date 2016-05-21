#ifndef DELAYFUNCTIONS_H
#define DELAYFUNCTIONS_H

#include "Arduino.h"

void delayWithIRAvoidance(int delayTime) {
  for(int i=0; i<delayTime*10; i++) {
    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);
    avoidObjects(irDistLeft, irDistRight);
    delay(100);
  }  
}

void delayWithWhiskerAvoidance(int delayTime) {
  for(int i=0; i<delayTime*20; i++) {
    avoidance_whiskers();
    delay(50);
  }  
}
#endif
