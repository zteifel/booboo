
#include <Servo.h> // Include servo library
#include <EEPROM.h>
#include "declarations.h"
#include "movement.h"
#include "ping_basic.h"
#include "beeps.h"
#include "ping_scan_utils.h"
#include "ping_analyze_scan.h"
#include "irDistance.h"
#include "Avoidance.h"
#include "IR_beacon_nav.h"
#include "onBlackPaper.h"

bool foundCylinder = false;
int currentState;
unsigned long time;


void setup() {

  Serial.begin(9600);

  servoLeft.attach(leftServoPin);
  servoRight.attach(rightServoPin);
  
  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
  
  pinMode(IR_BEACON_L_PIN, INPUT);
  pinMode(IR_BEACON_R_PIN,INPUT);
  
  pinMode(GALV_PIN, INPUT);
  pinMode(stopOnBlackPin, INPUT);

  Serial.flush();

  currentState = 4;

}

void loop() {
  Serial.println(currentState); // DEBUG
  
  // MEASURE DATA
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  
  if (currentState == 0) {
    // State 0: Move forward a set number of steps and then go to state 1. Avoid any objects.

    for (int i = 1; i < roamingTime*10; i++) {
      irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
      irDistRight = irDistance(irLEDPinRight, irRecPinRight);
      avoidObjects(irDistLeft, irDistRight);
      delay(100);
    }

    currentState = 1;
    
  } else if (currentState == 1) {
    // State 1: Use the sonar to search and find direction to a cylinder.

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
      currentState = 0;
    }
    else{
      headingIndex = cylinderIndex;
      currentState = 2;
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
    
    //////////////////////////////
    // Set the timer for state 2
    if (currentState == 2){
      time = millis();
    }
  
  } else if (currentState == 2) {
    // State 2: Move towards a cylinder using IR to correct the path,
    // stop the robot once the element gets a connection.
    
    if(millis() - time > msMoveForward){
      currentState = 1;
    }

    irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
    irDistRight = irDistance(irLEDPinRight, irRecPinRight);
    
    if (foundCylinder) {
      stopMovement();
      currentState = 3;
    } else {
      galvReading = digitalRead(GALV_PIN);
      if (galvReading == HIGH) {
        foundCylinder = true;
      } else if (irDistLeft < 0.8) {
        turnLeft();
      } else if (irDistRight < 0.8) {
        turnRight();
      } else {
        moveForwardSlow();
      }
    }
    
  } else if (currentState == 3) {
    // Collect cylinder
    beep3(); // DEBUG
    delay(500);
    //stopMovement();
    
    currentState = 4;
  } else if (currentState == 4) {
    // Go towards beacon

    steerTowardsBeacon();
    Serial.println("Beacon loop");
    
    while(!onBlackPaper()) {
      avoidObjects(irDistLeft,irDistRight);
      checkForBeacon(100);
      steerTowardsBeacon();
    }
    Serial.println("Stopped on black");
    currentState = 5;
    
  } else if (currentState == 5) {
    // Leave cylinder
    stopMovement();
    delay(2000);
    currentState = 4;  // For now
  }
}

void resetMeasurements(){
    for(int i=0; i < nMeasurements; i++){
      measurements[i]=0;
      noCylinder[i]=false;
    }
}
