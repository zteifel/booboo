#include <Servo.h>

const int WHISKER_L_PIN  = A2;
const int WHISKER_R_PIN = A3;


const float analogConversionFactor = 5.0 / 1024.0;
float whiskerLVal, whiskerRVal;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(WHISKER_L_PIN, INPUT);
  pinMode(WHISKER_L_PIN,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
}

void loop() {
  whiskerLVal = analogRead(WHISKER_L_PIN) * analogConversionFactor;  
  whiskerRVal = analogRead(WHISKER_R_PIN) * analogConversionFactor;
  float a0 = analogRead(A0) * analogConversionFactor;
  float a1 = analogRead(A1) * analogConversionFactor;
  float a4 = analogRead(A4) * analogConversionFactor;  
  float a5 = analogRead(A5) * analogConversionFactor;  

  Serial.println(
    "A0: " +String(a0) + "\t" +
    "A1: " +String(a1) + "\t" +
    "A2: " +String(whiskerLVal) + "\t" +
    "A3: " +String(whiskerRVal) + "\t" +
    "A4: " +String(a1) + "\t" +
    "A5: " +String(a1)
  );
 /* Serial.println(
    "Left: " +String(whiskerLVal) + "\t" +
    "Right: "+String(whiskerRVal)
  ); */
}
