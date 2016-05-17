#ifndef IR_BEACON_NAV_H
#define IR_BEACON_NAV_H

#include "Arduino.h"

void steerTowardsBeacon(){
  curTime = millis();
  if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
      (curTime  - beaconRightTimer <= beaonTimerTreshold)){
    moveForward();
    //Serial.println("Turn right "+String(beaconLeftCount - beaconRightCount));
  } else { 
      if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
         (curTime  - beaconRightTimer > beaonTimerTreshold)){
              turnLeftSlow();
      } else {
        turnRightSlow();
      }
      
  }
}

void checkForBeacon(int milliseconds){
  //for(int i=0; i<milliseconds/10; i++){
    beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
    beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;
    
    if(beaconLeftVal == 0) {
      beaconLeftTimer = millis();
    };
    if(beaconRightVal == 0) {
      beaconRightTimer = millis();
    }
  //   delay(10);
  //}
}

/*
void initialBeaconScan(){
  Serial.println("Initial bacon scan!");
  bool foundSomething = false;
  int pauseTime = 500;
  while(!foundSomething){
    stopMovement();
    for(int i=0; i<pauseTime/10; i++){
      beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
      beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;
      delay(10);
      if(beaconLeftVal == 0 && beaconRightVal == 0){
        Serial.println("Initial bacon scan complete");
        tone(6,1000,500);
        foundSomething = true;
        break;
      }
    }
    turnLeft();
    delay(100);
  } 
  stopMovement();
}
*/

/*
void initialBeaconScan(){
turnLeftSlow();
bool foundBeacon = false;
beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor; 
beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;

if(beaconLeftVal == 0 && beaconRightVal == 0){
   Serial.println("Initial bacon scan complete");
   tone(6,1000,500);
   foundSomething = true;
   break;
 }


}
*/

#endif
