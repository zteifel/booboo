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

// Constants for servo
int servoOffset = 4;
int servoLeftForward = 1550;
int servoLeftBackward = 1450 - servoOffset;
int servoRightForward = 1450 - servoOffset;
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

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  Serial.begin(9600);
  
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
    reading = digitalRead(BLACK_READ_PIN);  
    if(reading == HIGH){
      stopMovement();
    } else {
      moveForward();
    }
    delay(500);
  }
}

void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
