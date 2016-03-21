   #include <Servo.h>          // Include servo library
  
  Servo servoLeft;
  Servo servoRight;
  
  void setup() {
    // put your setup code here, to run once:
    
  Serial.begin(9600);
  Serial.println("BooBoo initiated!"); 
  servoLeft.attach(13);
  servoRight.attach(12);
  tone(4, 2000,500);
  delay(1000);
  tone(4, 2000, 500);
  delay(500);
  }
  
  void loop() {
    // put your main code here, to run repeatedly:
    
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(3000);
  }
