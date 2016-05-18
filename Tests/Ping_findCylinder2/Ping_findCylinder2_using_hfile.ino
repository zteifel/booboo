// Test of the ping sensor. Rotates the robot 
// around and gathers measurements;

#include <Servo.h> // Include servo library
#include "declarations.h"
#include "movement.h"
//#include "ping_basic.h"
#include "beeps.h"
//#include "ping_scan_utils.h"
//#include "ping_analyze_scan.h"
#include "ping_scan2.h"

void setup() {
  Serial.begin(9600);
  servoLeft.attach(leftServoPin);
  servoRight.attach(rightServoPin);
  delay(2000);
}

void loop(){
  ping_scan();
  delay(2000);
}
