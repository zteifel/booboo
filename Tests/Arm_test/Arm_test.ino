#include <Servo.h>

const int ARM_SERVO_PIN = 11;
int offset = 30;


Servo armServo;

void setup() {
  armServo.attach(ARM_SERVO_PIN);

}

void loop() {
  armServo.write(180-offset*2);   // Rotate servo counter clockwise
  delay(2000);          // Wait 2 seconds
  armServo.write(0+offset);     // Rotate servo clockwise
  delay(2000);
  armServo.write(90);    // Rotate servo to center
  delay(2000); 

}
