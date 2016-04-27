
#ifndef IR_rangeZone_detection_h
#define IR_rangeZone_detection_h

#include "Arduino.h"

class IR_rangeZone_detection
{
  public:
    IR_rangeZone_detection();
    float irDistance(int irLedPin, int irReceivePin);
    float irDetect(int irLedPin, int irReceiverPin, long frequency);
    float getLeftDistance();
    float getRightDistance();
};

#endif
