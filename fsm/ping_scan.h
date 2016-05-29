#ifndef PING_SCAN_H
#define PING_SCAN_H

#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "ping_analyze_scan.h"

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
      noCylinder[i]=false;
    }
}

// State 1: Use the sonar to search and find direction to a cylinder.
void ping_scan(){
    // Clear measurement data
    resetMeasurements();
    
    //////////////////////////////
    // Rotate continuously and measure
    rotate(counterClockwise, rotationSpeed);
    for(int i=0; i<nMeasurements; i++){
      measurements[i] = measurePingDist();
      delay(msPerStep-7); // -7 since this is the delay in the measurement
    }
    stopMovement();
  
    //////////////////////////////
    // Update the auxiliary array
    for(int i=0; i<nMeasurements; i++){
      if(measurements[i] > discardCylDist){
        noCylinder[i] = true;
      }
    }
    
    beep2(); // DEBUG
    Serial.println("Entering findCylinder"); // DEBUG
  
    //////////////////////////////
    // Run main search algorithm
    int cylinderIndex = findCylinder();
    int headingIndex;
    beep3(); // DEBUG
    
    if(cylinderIndex == noCylFound){
      Serial.println("Entering getIndexOfLargestOpenInterval"); // DEBUG
      headingIndex = getIndexOfLargestOpenInterval();
      currentState = STATE_MOVE_AND_AVOID;
    }
    else{
      headingIndex = cylinderIndex;
      currentState = STATE_CATCH_CYLINDER;
    }
  
    Serial.println("Entering rotation"); // DEBUG
  
    //////////////////////////////
    // Rotate towards cylinder/large open space
    if(headingIndex != noCylFound){
      if(headingIndex <= nMeasurements/2){
        rotate(counterClockwise, rotationSpeed);
        delay(msPerStep * headingIndex);
      }else{
        rotate(clockwise, rotationSpeed);
        delay(msPerStep * (nMeasurements - headingIndex));
      }
    }
    stopMovement();
}

#endif
