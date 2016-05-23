#include "Arduino.h"

#ifndef AVOIDANCE_H
#define AVOIDANCE_H


bool avoidObjects(float irDistLeft, float irDistRight) {


  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
    Serial.println("IR Avoidance: Reversing");
    Serial.print(irDistLeft);
    Serial.print("  ");
    Serial.println(irDistRight);
    return true;
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    //Serial.println("Right");
    return true;
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    //Serial.println("Left");
    return true;
  } else {
    return false;
  }
}


#endif
