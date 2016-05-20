#ifndef IR_BEACON_NAV_H
#define IR_BEACON_NAV_H

#include "Arduino.h"

void steerTowardsBeacon(){
  curTime = millis();
  if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
      (curTime  - beaconRightTimer <= beaonTimerTreshold)){
    moveForward();
  } else if ((curTime  - beaconLeftTimer > beaonTimerTreshold) &&
	         (curTime  - beaconRightTimer <= beaonTimerTreshold)){
    turnRightSlow();
  } else {
    turnLeftSlow();
  }
}

void checkForBeacon(int milliseconds){
    beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
    beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;
    
    if(beaconLeftVal == 0) {
      beaconLeftTimer = millis();
      lastBeaconTime = millis();
    };
    if(beaconRightVal == 0) {
      beaconRightTimer = millis();
      lastBeaconTime = millis();
    }
}


#endif
