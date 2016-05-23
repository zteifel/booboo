#include "Arduino.h"

#ifndef AVOIDANCE_H
#define AVOIDANCE_H


void avoidObjects(float irDistLeft, float irDistRight) {


  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
    Serial.println("IR Avoidance: Reversing");
    Serial.print(irDistLeft);
    Serial.print("  ");
    Serial.println(irDistRight);
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    //Serial.println("Right");
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    //Serial.println("Left");
  //} else {
    //moveForward();
  }
}


#endif
