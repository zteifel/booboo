#ifndef PING_ANALYZE_SCAN_H
#define PING_ANALYZE_SCAN_H


bool couldIntervalBeCylinder(int intervalLength, int intervalDist){
  //delay(1000); //DEBUG
  //for(int i=0; i<intervalLength; i++){ //DEBUG beep once per interval index
  //  tone(beepPin, 1000, 500);
  //  delay(1000);
  //}
  //delay(1000); //DEBUG
  return intervalLength <= 5;
}

// Determines the index of the best cylinder candidate
// Finds the middle of the interval containing the
// closest measured point. If that distance is too large
// to be a cylinder, check the next-to-closest interval.
// If no intervals can be cylinders, call
// getIndexOfLargestOpenInterval to get a free new direction
// to explore.
int findCylinder(){
  while(true){
    Serial.println("findCylinder: outer loop"); // DEBUG
    int nearestIndex = getIndexMin(measurements, noCylinder, nMeasurements);
    
    if(nearestIndex == noCylFound){
      Serial.println("No cylinder found in scan"); // DEBUG
      return noCylFound;
    }
    
    int iL = prevIndex(nearestIndex, nMeasurements);
    int iR = nextIndex(nearestIndex, nMeasurements);
    int intervalLength = 0;
  
    while(abs(measurements[nearestIndex] - measurements[iL]) < 5){
      iL = prevIndex(iL, nMeasurements);
      intervalLength++;
      //if(iL == iR)
        //break;
      Serial.println("findCylinder: iL="+String(iL)); // DEBUG
    }
    while(abs(measurements[nearestIndex] - measurements[iR]) < 5){
      iR = nextIndex(iR, nMeasurements);
      intervalLength++;
      //if(iL == iR)
        //break;
      Serial.println("findCylinder: iR="+String(iR)); // DEBUG
    }
    
    if(couldIntervalBeCylinder(intervalLength, measurements[nearestIndex])){
      Serial.println(
        "Found cyl in interval of length "+String(intervalLength)+
        " at dist "+String(measurements[nearestIndex])
      ); // DEBUG
      return periodicBoundary(iL + intervalLength/2, nMeasurements);
    } else {
      Serial.println(
        "No cylinder found in interval of length "+String(intervalLength)+
        " at dist "+String(measurements[nearestIndex])
      ); // DEBUG
      for(int i=nextIndex(iL, nMeasurements); i!=iR; i=nextIndex(i, nMeasurements)){
        noCylinder[i] = true; 
        Serial.println("index "+String(i)+" not cylinder"); // DEBUG
      }
    }
  }
}

// Index of the broadest open horizon.
int getIndexOfLargestOpenInterval(){
  int lenLargest = 0;
  int iLeftLargest = 0;
  int iRightLargest = 0;
  int nbrOfRightChecks = 0;  

  int iLeft;
  int iRight;
  int i=-1;
  while(true) {

    Serial.println("Largest open intervall");
    //Take step into possible new intervall:
    iLeft = nextIndex(i,nMeasurements);
    
    iRight = iLeft;
    
    int intervalWidth = 0;
    while(measurements[iLeft] > horizonDist){
      //Serial.println("First loop");
      iLeft = prevIndex(iLeft,nMeasurements);
      intervalWidth++;
      if(iLeft==iRight)
        break;
    }
    while(measurements[iRight] > horizonDist){
      //Serial.println("Second loop");
      iRight = nextIndex(iRight,nMeasurements);
      intervalWidth++;
      nbrOfRightChecks++;
      if(iLeft==iRight)
        break;
    }
    if(intervalWidth > lenLargest){
      lenLargest = intervalWidth;
      iLeftLargest = iLeft;
      iRightLargest = iRight;
    }
    
    i = nextIndex(iRight, nMeasurements);
    nbrOfRightChecks++;
    
    // When all points have been examined, continue!
    if(nbrOfRightChecks > nMeasurements){
      break;
    }
  }
  
  return periodicBoundary(iLeftLargest + lenLargest/2, nMeasurements);
}

#endif
