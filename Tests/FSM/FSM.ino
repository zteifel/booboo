#include <Servo.h>

// Pins
const int IR_REC_PIN_LEFT = 5;    // 200 ohm resistor
const int IR_REC_PIN_RIGHT = 4;  // 200 ohm resistor
const int IR_LED_PIN_LEFT = 3;   // 1.8k ohm resistor
const int IR_LED_PIN_RIGHT = 2;  // 1.8k ohm resistor
const int READ_PIN    = 9;
const int SERVO_L_PIN = 13;
const int SERVO_R_PIN = 12;
const int BUTTON_PIN = 8;
const int SPEAKER_PIN = 7; // Status speaker, resistor?
const int ULTRA_SOUND_PIN = 6;
const int GALV_PIN = 10;

// Constants for servo
Servo servoRight;
Servo servoLeft;
int servoLeftForward = 1550;
int servoLeftBackward = 1450;
int servoRightForward = 1450;
int servoRightBackward = 1550;
float irDistThreshold = 0.6;

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


int reading;
int buttonState;
bool buttonPressed;
int numberOfStates = 4;
int currentState = 0;
bool foundBlack = false;
bool foundCylinder = false;
int galvReading = 0;


void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  pinMode(READ_PIN, INPUT);

  Serial.begin(9600);
  Serial.flush();

  servoLeft.attach(SERVO_L_PIN);
  servoRight.attach(SERVO_R_PIN);

  pinMode(IR_REC_PIN_LEFT, INPUT);  pinMode(IR_LED_PIN_LEFT, OUTPUT);   // IR LED & Receiver
  pinMode(IR_REC_PIN_RIGHT, INPUT);  pinMode(IR_LED_PIN_RIGHT, OUTPUT);

  pinMode(GALV_PIN, INPUT);
  
  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    buttonPressed = true;
  } else {
    if (buttonPressed) {
      currentState = (currentState + 1) % numberOfStates;
      buttonPressed = false;
      Serial.print("Pressed!");
      Serial.print("  ");
      Serial.println(currentState);
    } else {
      buttonPressed = false;
    }
  }
  
  if (currentState == 0) {
    // Initilization, robot stays idle
    stopMovement();
    
  } else if (currentState == 1) {
    // Stop on black
    reading = digitalRead(READ_PIN);  
    if(reading == LOW) {
      if (foundBlack) {
        stopMovement();
      } else {
        delay(1000);
        stopMovement();
        foundBlack = true;
      }
    } else {
      if (foundBlack) {
        foundBlack = false;
      } else {
      moveForward();
      }
    }
    //delay(500);
  } else if (currentState == 2) {
    // Object avoidance
    irDistLeft = irDistance(IR_LED_PIN_LEFT, IR_REC_PIN_LEFT);         // Measure distance
    irDistRight = irDistance(IR_LED_PIN_RIGHT, IR_REC_PIN_RIGHT);

    avoidObjects(irDistLeft, irDistRight);
    
    
  } else if (currentState == 3) {
    irDistLeft = irDistance(IR_LED_PIN_LEFT, IR_REC_PIN_LEFT);         // Measure distance
    irDistRight = irDistance(IR_LED_PIN_RIGHT, IR_REC_PIN_RIGHT);

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
}

void avoidObjects(float irDistLeft, float irDistRight) {

  if (irDistLeft < irDistThreshold && irDistRight < irDistThreshold) {
    reverse();
  } else if (irDistLeft < irDistThreshold) {
    turnRight();
    //Serial.println("Right");
  } else if (irDistRight < irDistThreshold) {
    turnLeft();
    //Serial.println("Left");
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

void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
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
