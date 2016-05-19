#include "Arduino.h"

#ifndef AVOIDANCE_H
#define AVOIDANCE_H


void avoidObjects(float irDistLeft, float irDistRight) {


  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    //Serial.println("Right");
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    //Serial.println("Left");
  }
}


#endif
