#include "beeps.h"
#include "Arduino.h"
#include "declarations.h"

void beep() {
  for (int i=1000; i<2000; i=i*1.02) {
    tone(beepPin,i,10);
    delay(20); 
  }
  for (int i=2000; i>1000; i=i*.98) {
    tone(beepPin,i,10);
    delay(20);
  }
}

void beep2(){
  tone(beepPin, 1000, 1000);
  delay(500);
}

void beep3(){
  tone(beepPin, 2000, 1000);
  delay(500);
}

void error(){
  tone(beepPin, 1000, 5000);
}
