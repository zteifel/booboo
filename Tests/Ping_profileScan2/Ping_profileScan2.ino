// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "ping_analyze_scan.h"

void setup() {
  Serial.begin(9600);
  tone(beepPin, 2000, 500);
  servoLeft.attach(13);
  servoRight.attach(12);
  delay(2000); 
}

void loop(){
  // Clear measurement data
  resetMeasurements();
  
  //////////////////////////////
  // Rotate continually and measure
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
  
  Serial.println("Entering findCylinder"); // DEBUG

  //////////////////////////////
  // Run main search algorithm
  int cylinderIndex = findCylinder();
  int headingIndex;
  
  if(cylinderIndex == noCylFound){
    Serial.println("Entering getIndexOfLargestOpenInterval"); // DEBUG
    headingIndex = getIndexOfLargestOpenInterval();
  }
  else{
    headingIndex = cylinderIndex;
  }

  Serial.println("Entering rotation"); // DEBUG
  beep2();

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

  //////////////////////////////
  // Signal done and wait
  beep();
  delay(2000);
  
  //////////////////////////////
  // Tell the with of the aquired target with a binary beep sequence
  binaryNumberBeep(targetWidth);
  beep();
  writeToMemory();
  delay(2000);
}

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
      noCylinder[i]=false;
    }
}
