#ifndef ONBLACKPAPER_H
#define ONBLACKPAPER_H

#include "Arduino.h"

bool onBlackPaper(){

  return(digitalRead(stopOnBlackPin) == LOW);

}
#endif
