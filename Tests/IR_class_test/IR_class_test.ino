//#include <declarations.h>
#include <IR_rangeZone_detection.h>

IR_rangeZone_detection IR;
float irDistLeft, irDistRight;

void setup()                                 // Built-in initialization block
{
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  IR.init();
  //tone(speakerPin, 2000,500);
  //delay(1000);
  //tone(speakerPin, 2000, 500);

  //pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  //pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
}  

void loop() {
  // put your main code here, to run repeatedly:
  
  irDistLeft = IR.getLeftDistance();
  irDistLeft = IR.getRightDistance();
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight);

}
