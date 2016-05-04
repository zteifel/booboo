#ifndef PING_SCAN_UTILS_H
#define PING_SCAN_UTILS_H

#include "Arduino.h"

int getIndexMin(int* measurements, int* noCylinder, int maxIndex);
int prevIndex(int index, int arrayLength);
int nextIndex(int index, int arrayLength);
int periodicBoundary(int index, int length);
String arrayToString(int array[], int arrayLength);

#endif
