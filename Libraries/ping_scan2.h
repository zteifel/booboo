#ifndef PING_SCAN_H
#define PING_SCAN_H

#include "Arduino.h"
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "ping_analyze_scan.h"
#include <Average.h>

const int maxCylWidth = 7;
const int minCylDepth = 5;
const int maxCylDist = 60;
const int timeOut = 100;

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
    }
}

// State 1: Use the sonar to search and find direction to a cylinder.
void ping_scan(){
  int scan_steps = 0;
  
  while(scan_steps < pingTimeOut){
    scan_steps++;
    
    resetMeasurements();
    measurements[1] = measurePingDist();
    Serial.println(String(measurements[1])); // DEBUG
    
    rotate(counterClockwise, rotationSpeed);
    while(true){
      measurements[0] = measurements[1];
      measurements[1] = measurePingDist();
      Serial.println(String(measurements[1])); // DEBUG
      delay(msPerStep-7);
      if( (measurements[0] - measurements[1]) > minCylDepth && measurements[1] < maxCylDist){
        break;
      }
    }
    stopMovement();
    
    beep2();
    
    int intervalLength = 0;
    int i = 1;
    rotate(counterClockwise, rotationSpeed);
    while(true){
      i++;
      intervalLength++;
      measurements[i] = measurePingDist();
      Serial.println(String(measurements[i])); // DEBUG
      delay(msPerStep-7);
      if(measurements[i] - measurements[i-1] > minCylDepth){// || intervalLength > maxCylWidth){
        break;
      }
    }
    stopMovement();
    
    beep3();
    
    delay(3000);
    binaryNumberBeep(intervalLength);
    
    if(intervalLength < maxCylWidth){
      rotate(clockwise, rotationSpeed);
      delay(msPerStep * intervalLength/2);
      stopMovement();
      beep();
      return;
    }
  }
  
  /*
  if(scan_steps >= pingTimeOut){
    rotate(clockwise, rotationSpeed);
    delay(msPerStep * intervalLength/2);
    stopMovement();
    return;
  }
  */
  
}

bool isCylinder(int measurements[nMeasurements], int intervalLength) {

    if (minimum(measurements, intervalLength) < 20) {
        if (intervalLength <= 8) {
            return true;
        }else{
            return false;
        }
    }else if(minimum(measurements, intervalLength) < 30) {
        if (intervalLength <= 7) {
            return true;
        }else{
            return false;
        }
    }else if(minimum(measurements, intervalLength) < 40) {
        if (intervalLength <= 5) {
            return true;
        }else{
            return false;
        }
    }else{
        if (intervalLength <= 4) {
            return true;
        }else{
            return false;
        }
    }
}


}
#endif
