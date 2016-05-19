#ifndef PING_SCAN2_H
#define PING_SCAN2_H

#include "Arduino.h"
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"

/*
const int maxCylWidth = 7;
const int minCylDepth = 5;
const int maxCylDist = 60;
const int timeOut = 100;
*/

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
    }
}

int minimum(int measurements[nMeasurements], int intervalLength) {
  int minValue = 10000;
  for (int i = 1; i < intervalLength; i++) {
      if (measurements[i] < minValue && measurements[i] > 0) {
        minValue = measurements[i];
      }
  }
  return minValue;
}

bool isCylinder(int measurements[nMeasurements], int intervalLength) {
  int minValue = minimum(measurements, intervalLength);

    if (minValue < 20) {
        if (intervalLength <= 9) {
            return true;
        }else{
            return false;
        }
    }else if(minValue < 30) {
        if (intervalLength <= 8) {
            return true;
        }else{
            return false;
        }
    }else if(minValue < 40) {
        if (intervalLength <= 7) {
            return true;
        }else{
            return false;
        }
    }else{
        if (intervalLength <= 6) {
            return true;
        }else{
            return false;
        }
    }
}


// OBS! Ta inte bort serial-println-raderna! Programmet funkar inte utan dem (otroligt konstigt).

// State 1: Use the sonar to search and find direction to a cylinder.
void ping_scan(){
  
  while(true){
    
    // If time out, rotate to a random direction and exit to roam state
    if(millis() - time > timeOut_ping){
      int randomDir = random(50);
      rotate(clockwise, rotationSpeed);
      delay(msPerStep * randomDir);
      stopMovement();
      currentState = STATE_MOVE_AND_AVOID;
      return;
    }
    
    // Reset the buffer
    resetMeasurements();
    measurements[1] = measurePingDist();
    Serial.println("Latest measurement: "+String(measurements[1])); // DEBUG
    
    // Scan for a right edge
    rotate(counterClockwise, rotationSpeed);
    while(millis() - time < timeOut_ping){
      measurements[0] = measurements[1];
      measurements[1] = measurePingDist();
      Serial.println("Latest measurement: "+String(measurements[1])); // DEBUG
      delay(msPerStep-7);
      if( (measurements[0] - measurements[1]) > minCylDepth && measurements[1] < maxCylDist){
        break;
      }
    }
    stopMovement();
    
    beep2();
    
    // Scan for a left edge
    int intervalLength = 0;
    int i = 1;
    rotate(counterClockwise, rotationSpeed);
    while(millis() - time < timeOut_ping){
      i++;
      intervalLength++;
      measurements[i] = measurePingDist();
      Serial.println("Latest measurement: "+String(measurements[i])); // DEBUG
      delay(msPerStep-7);
      if(measurements[i] - measurements[i-1] > minCylDepth){
        break;
      }
      // Reset the interval scan if a new right edge is found. (TODO This needs improvement)
      /*
      if( (measurements[i-1] - measurements[i]) > minCylDepth && measurements[i] < maxCylDist){
        stopMovement();
        beep2();
        int tmp1 = measurements[i], tmp0 = measurements[i-1];
        resetMeasurements();
        measurements[0] = tmp0;
        measurements[1] = tmp1;
        i = 1;
        intervalLength = 0;
        rotate(counterClockwise, rotationSpeed);
      }
      */
    }
    stopMovement();
    
    beep3();
    
    //delay(3000); // DEBUG
    //binaryNumberBeep(intervalLength); // DEBUG
    
    // Check if the interval is a cylinder and rotate towards it
    if(isCylinder(measurements, intervalLength)){
    //if(intervalLength < maxCylWidth){
      rotate(clockwise, rotationSpeed);
      delay(msPerStep * intervalLength/2);
      stopMovement();
      beep();
      currentState = STATE_CATCH_CYLINDER;
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

#endif
