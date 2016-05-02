#include <Servo.h>     

// Pins
const int IR_REC_PIN_LEFT = 5;    // 200 ohm resistor
const int IR_REC_PIN_RIGHT = 4;  // 200 ohm resistor
const int IR_LED_PIN_LEFT = 3;   // 1.8k ohm resistor
const int IR_LED_PIN_RIGHT = 2;  // 1.8k ohm resistor
const int SERVO_L_PIN = 13;
const int SERVO_R_PIN = 12;
const int GALV_PIN = 10;

// Constants for IR
int irMaxFreq = 58000;
int irOptFreq = 38000;
int irFreqStep = 5000;
int nbrIRDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;

const int servoLeftForward = 1530;
const int servoLeftBackward = 1470;
const int servoRightForward = 1470;
const int servoRightBackward = 1530;

bool foundCylinder = false;
int galvReading = 0;

Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  //tone(4, 2000,500);
  //delay(1000);
  //tone(4, 2000, 500);

  pinMode(IR_REC_PIN_LEFT, INPUT);  pinMode(IR_LED_PIN_LEFT, OUTPUT);   // IR LED & Receiver
  pinMode(IR_REC_PIN_RIGHT, INPUT);  pinMode(IR_LED_PIN_RIGHT, OUTPUT);

  pinMode(GALV_PIN, INPUT);

  servoLeft.attach(SERVO_L_PIN);
  servoRight.attach(SERVO_R_PIN);

}

void loop() {
  float irDistLeft = irDistance(IR_LED_PIN_LEFT, IR_REC_PIN_LEFT);         // Measure distance
  float irDistRight = irDistance(IR_LED_PIN_RIGHT, IR_REC_PIN_RIGHT);

  //Serial.print(irDistLeft);
  //Serial.print("  ");
  //Serial.println(irDistRight);

  if (foundCylinder) {
    stopMovement();
  } else {
  galvReading = digitalRead(GALV_PIN);
  if (galvReading == HIGH) {
    foundCylinder = true;
    //Serial.println("Galv!");
  } else if (irDistLeft < 0.8) {
    turnLeft();
  } else if (irDistRight < 0.8) {
    turnRight();
  } else {
    moveForward();
    //Serial.println("Low");
  }
  }

}

// IR distance measurement function
float irDistance(int irLedPin, int irReceivePin)
{ 
  float nbrAvgIrRuns = 5.0;
  float meanDistZone;
  float sumDistZones = 0.0;
  
  for(int k = 1; k<= nbrAvgIrRuns; k++) { 
    float distance = 0.0;
    for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
      distance += irDetect(irLedPin, irReceivePin, f);
    }
    sumDistZones += distance;
  }
  meanDistZone = sumDistZones/nbrAvgIrRuns;

  return meanDistZone/nbrIRDistZones; // Normalize to 1
}

// IR Detection function
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);             // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}


void moveForward() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightForward);
}

void turnLeft() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightForward);
}

void turnRight() {
  servoLeft.writeMicroseconds(servoLeftForward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void reverse() {
  servoLeft.writeMicroseconds(servoLeftBackward);
  servoRight.writeMicroseconds(servoRightBackward);
}

void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
