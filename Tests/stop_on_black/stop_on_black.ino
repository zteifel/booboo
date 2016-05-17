#include <Servo.h> // Include servo library
    
Servo servoLeft;
Servo servoRight;

const int READ_PIN    = 9;
const int SERVO_L_PIN = 13;
const int SERVO_R_PIN = 12;

int reading;

void setup()
{
  pinMode(READ_PIN, INPUT);
  Serial.begin(9600);
  
  servoLeft.attach(SERVO_L_PIN);
  servoRight.attach(SERVO_R_PIN);
}

void loop()
{
  reading = digitalRead(READ_PIN);  
  if(reading == LOW){
    stopMovement();
  }else{
    moveForward();
  }
  delay(500);
}

void stopMovement(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void moveForward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}
