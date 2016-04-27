#include "IR_rangeZone_detection.h"

IR_rangeZone_detection irrzd;

float irDistLeft, irDistRight;

void setup()                                 // Built-in initialization block
{
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
}
 
void loop()                                  // Main loop auto-repeats
{
  irDistLeft = irrzd.getLeftDistance();        // Measure distance
  irDistRight = irrzd.getRightDistance();
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight); 
  //delay(100);                                // 0.1 second delay
}
