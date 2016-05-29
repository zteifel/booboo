#ifndef IR_BEACON_NAV_H
#define IR_BEACON_NAV_H

#include "Arduino.h"

void steerTowardsBeacon(){
  curTime = millis();
  if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
      (curTime  - beaconRightTimer <= beaonTimerTreshold)){
    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);    
    if (!avoidObjects(irDistLeft, irDistRight)){
      moveForward();
    }
    delay(100);
    lastPosChangeTimer = millis();
  //} 
  //else if ((curTime  - beaconLeftTimer > beaonTimerTreshold) &&
  //           (curTime  - beaconRightTimer <= beaonTimerTreshold)){
  //  turnRightSlow();
  } else {
    turnLeftSlow();
  }
}

void checkForBeacon(){
    beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
    beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;
    
    if(beaconLeftVal == 0) {
      beaconLeftTimer = millis();
    };
    if(beaconRightVal == 0) {
      beaconRightTimer = millis();
    }
    
    //lastBeaconTimer = max(beaconLeftTimer, beaconRightTimer);
}

void moveToBeacon() {
  lastPosChangeTimer = millis();  // Init
    
  while( onBlackPaper() == false){ // Note: the onBlackPaper function didn't work for some reason.
    checkForBeacon();
    steerTowardsBeacon();

    if(millis() - lastPosChangeTimer > timeOut_beacon) {
      Serial.println("Performing a random walk to find beacon");
      randomWalk(0, 50, 5); // Randomwalk 360 deg during 5sec
      lastPosChangeTimer = millis();  // Init
    }
  }
  Serial.println("Stopped on black");
  stopOnBlackCount = 0;
  currentState = STATE_DROP_CYLINDER;
}

#endif
