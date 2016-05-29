#ifndef beeps_H
#define beeps_H

#include "beeps.h"
#include "Arduino.h"

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
  tone(beepPin, 500, 1000);
  delay(500);
}

void beep3(){
  tone(beepPin, 2000, 1000);
  delay(500);
}

void error(){
  tone(beepPin, 1000, 5000);
}

void binaryNumberBeep(int decimalNumber){
  // Largest position first. Ex: 100 -> 4
  int remainder, quotient;
  int binaryNumber[100], i=1, j;

  quotient = decimalNumber;

  while(quotient!=0){
    binaryNumber[i++]= quotient % 2;
    quotient = quotient / 2;
  }

  for(j = i -1 ;j> 0;j--){
    //printf("%d",binaryNumber[j]);
    if(binaryNumber[j] == 1){
      beep3(); // High pitch == 1
    }else{
      beep2(); // Low  pitch == 0
    }
    delay(1000);
  }
  /*
  for(int i=0; i<decimalNumber; i++){
    beep3();
    delay(1000);
  }
  */
}

#endif
