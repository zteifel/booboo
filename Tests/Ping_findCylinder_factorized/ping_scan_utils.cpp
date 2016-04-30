
#include "ping_scan_utils.h"
#include "Arduino.h"

// Index of the closest measured distance
int getIndexMin(int* measurements, int* noCylinder, int maxIndex){
  int minVal = 500; //Max
  int iMinVal = -1;
  
  for(int i=0; i<maxIndex; i++){
    if( !*(noCylinder+i) && (*(measurements+i) > 0) && (*(measurements+i) < minVal) ){
      iMinVal = i;
      minVal = *(measurements+i);
    }
  }
  return iMinVal;
}

// Gives previous index with wrap-around
int prevIndex(int index, int arrayLength){
  return (index+arrayLength-1) % arrayLength;
}

// Gives next index with wrap-around
int nextIndex(int index, int arrayLength){
  return (index+1) % arrayLength;
}

String arrayToString(int array[], int arrayLength)
{
  String s = "[ ";
  for(int i=0; i < arrayLength; i++){
    s+=String(array[i])+" ";
  }
  return s + "]";
}
