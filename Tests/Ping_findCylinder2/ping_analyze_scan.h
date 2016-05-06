#ifndef PING_ANALYZE_SCAN_H
#define PING_ANALYZE_SCAN_H


bool couldIntervalBeCylinder(int intervalLength, int intervalDist){
  // TODO Experimenting with the condition, use intervalDist
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
      return -1;
    }
    
    int iL = prevIndex(nearestIndex, nMeasurements);
    int iR = nextIndex(nearestIndex, nMeasurements);
    int intervalLength = 0;
  
    while(abs(measurements[nearestIndex] - measurements[iL]) < 5){
      iL = prevIndex(iL, nMeasurements);
      intervalLength++;
      Serial.println("findCylinder: inner loop 1"); // DEBUG
    }
    while(abs(measurements[nearestIndex] - measurements[iR]) < 5){
      iR = nextIndex(iR, nMeasurements);
      intervalLength++;
      Serial.println("findCylinder: inner loop 2"); // DEBUG
    }
    
    if(couldIntervalBeCylinder(intervalLength, measurements[nearestIndex])){
      return periodicBoundary(iL + intervalLength/2, nMeasurements);
    } else {
      for(int i=iL+1; i<iR; i=nextIndex(i, nMeasurements)){
        noCylinder[i] = true; 
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
    //Take step into possible new intervall:
    iLeft = nextIndex(i,nMeasurements);
    
    iRight = iLeft;
    
    int intervalWidth = 0;
    while(measurements[iLeft] > horizonDist){
      iLeft = prevIndex(iLeft,nMeasurements);
      intervalWidth++;
    }
    while(measurements[iRight] > horizonDist){
      iRight = nextIndex(iRight,nMeasurements);
      intervalWidth++;
      nbrOfRightChecks++;
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
