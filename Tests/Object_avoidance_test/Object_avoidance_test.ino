//#include "declarations.h"
#include <Servo.h>

// Pins for IR
int irRecPinLeft = 5;    // 200 ohm resistor
int irRecPinRight = 4;  // 200 ohm resistor
int irLEDPinLeft = 3;   // 1.8k ohm resistor
int irLEDPinRight = 2;  // 1.8k ohm resistor


// Other
int speakerPin = 7; // Status speaker, resistor?
int buttonPin = 8;  // Status speaker, resistor?
int ultraSoundPin = 6;


// Constants for IR
int irMaxFreq = 58000;
int irOptFreq = 38000;
int irFreqStep = 5000;
float irNbrDistZones = (irMaxFreq-irOptFreq)/irFreqStep+1;
float irNbrAvgRuns = 5.0;
float irMeanDistZone;
float irSumDistZones = 0.0;
float irTmpDist;
float irDistLeft, irDistRight;
float irDetected;

const int servoOffset = 4;
const int servoLeftForward = 1600;
const int servoLeftBackward = 1400;
const int servoRightForward = 1400;
const int servoRightBackward = 1600;
const float irDistThreshold = 0.5;

Servo servoLeft;
Servo servoRight;

void setup()                                 // Built-in initialization block
{
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  //tone(speakerPin, 2000,500);
  //delay(1000);
  //tone(speakerPin, 2000, 500);

  servoLeft.attach(13);
  servoRight.attach(12);

  Serial.flush();
  

  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
}  
 
void loop()                                  // Main loop auto-repeats
{

  
  irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  

  avoidObjects(irDistLeft, irDistRight);
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight);

  
}

void avoidObjects(float irDistLeft, float irDistRight) {


  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    Serial.println("Right");
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    Serial.println("Left");
  } else {
    moveForward();
  }
  


}

// IR distance measurement function

float irDistance(int irLedPin, int irReceivePin)
{ 
  irSumDistZones = 0.0;
  for(int k = 1; k<= irNbrAvgRuns ; k++) { 
    irTmpDist = 0.0;
    for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
      irTmpDist += irDetect(irLedPin, irReceivePin, f);
    }
    irSumDistZones  += irTmpDist;
  }
  irMeanDistZone = irSumDistZones/irNbrAvgRuns;

  return irMeanDistZone/irNbrDistZones; // Normalize to 1
}

// IR Detection function

float irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 10);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  irDetected = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return irDetected;                                 // Return 1 no detect, 0 detect
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

