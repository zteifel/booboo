/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
byte value;


void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);

  Serial.print("[");
  for (int address = 0; address < 50; address++) {
    value = EEPROM.read(address);
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.print("]");
}

void loop() {
  // read a byte from the current address of the EEPROM

  

  delay(50);
}
