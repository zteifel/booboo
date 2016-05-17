#include <Servo.h>

const int IR_BEACON_L_PIN  = A4;
const int IR_BEACON_R_PIN = A5;
const int SERVO_L_PIN = 13;
const int SERVO_R_PIN = 12;

// Constants for servo
Servo servoRight;
Servo servoLeft;
int servoLeftForward = 1530;
int servoLeftBackward = 1470;
int servoRightForward = 1470;
int servoRightBackward = 1530;

const float analogConversionFactor = 5.0 / 1024.0;
float beaconLeftVal, beaconRightVal;
float curTime, beaconLeftTimer, beaconRightTimer;
const float beaonTimerTreshold = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(IR_BEACON_L_PIN, INPUT);
  pinMode(IR_BEACON_R_PIN,INPUT);
  servoLeft.attach(SERVO_L_PIN);
  servoRight.attach(SERVO_R_PIN);

  initialBeaconScan();
}

void loop() {
  checkForBeacon(100);

  Serial.println("Left: "+String(curTime  - beaconLeftTimer)+" Right "+String(curTime  - beaconRightTimer));
  
  steerTowardsBeacon();
}

void steerTowardsBeacon(){
  curTime = millis();
  if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
      (curTime  - beaconRightTimer <= beaonTimerTreshold)){
    moveForward(servoLeft,servoRight);
    //Serial.println("Turn right "+String(beaconLeftCount - beaconRightCount));
  } else { 
      if ((curTime  - beaconLeftTimer <= beaonTimerTreshold) &&
         (curTime  - beaconRightTimer > beaonTimerTreshold)){
              turnLeft(servoLeft,servoRight);
      } else {
        turnRight(servoLeft,servoRight);
      }
      
  }
}
void checkForBeacon(int milliseconds){
  for(int i=0; i<milliseconds/10; i++){
    beaconLeftVal  = analogRead(IR_BEACON_L_PIN) * analogConversionFactor;  
    beaconRightVal = analogRead(IR_BEACON_R_PIN) * analogConversionFactor;
    
    if(beaconLeftVal == 0) {
      beaconLeftTimer = millis();
    };
    if(beaconRightVal == 0) {
      beaconRightTimer = millis();
    }
     delay(10);
  }
}

void initialBeaconScan(){
  Serial.println("Initial bacon scan!");
  bool foundSomething = false;
  int pauseTime = 500;
  while(!foundSomething){
    stopMovement(servoLeft,servoRight);
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
    turnLeft(servoLeft,servoRight);
    delay(100);
  } 
  stopMovement(servoLeft,servoRight);
}

void turnLeft(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoRightBackward);
  servoRight.writeMicroseconds(servoLeftForward);
}
void turnRight(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightForward);
}
void moveForward(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightForward);
}
void stopMovement(Servo servoLeft, Servo servoRight){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

