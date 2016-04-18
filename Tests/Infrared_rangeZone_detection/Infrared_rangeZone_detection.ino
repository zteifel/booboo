/*
 * Distance range is from 0 to 5.  Only a small range of several centimeters  
 * in front of each detector is measureable.  Most of it will be 0 (too 
 * close) or 5 (too far).
 */

int irLEDPinLeft = 9;
int irRecPinLeft = 10;
int irLEDPinRight = 2;
int irRecPinRight = 3;

int statusLedPinLeft = 7;
int statusLedPinRight = 6;

int irMaxFreq = 50000;
int irOptFreq = 38000;
int irFreqStep = 1000;
int nbrIRDistZones = (irMaxFreq-irOptFreq)/1000+1;

void setup()                                 // Built-in initialization block
{
  Serial.begin(9600);                        // Set data rate to 9600 bps
  Serial.println("BooBoo initiated!"); 
  tone(4, 2000,500);
  delay(1000);
  tone(4, 2000, 500);

  pinMode(irRecPinLeft, INPUT);  pinMode(irLEDPinLeft, OUTPUT);   // IR LED & Receiver
  pinMode(irRecPinRight, INPUT);  pinMode(irLEDPinRight, OUTPUT);
  pinMode(statusLedPinLeft, OUTPUT); pinMode(statusLedPinRight, OUTPUT);
}  
 
void loop()                                  // Main loop auto-repeats
{
  int irDistLeft = irDistance(irLEDPinLeft, irRecPinLeft);         // Measure distance
  int irDistRight = irDistance(irLEDPinRight, irRecPinRight);
  digitalWrite(statusLedPinLeft, LOW);
  digitalWrite(statusLedPinRight, LOW);
  
  
  if(irDistLeft != nbrIRDistZones){
      digitalWrite(statusLedPinLeft, HIGH);
    }
  
  if(irDistRight != nbrIRDistZones){
       digitalWrite(statusLedPinRight, HIGH); 
    }
  
  Serial.print(irDistLeft);
  Serial.print("  ");
  Serial.println(irDistRight); 
  delay(100);                                // 0.1 second delay
}

// IR distance measurement function

int irDistance(int irLedPin, int irReceivePin)
{  
  int distance = 0;
  for(long f = irOptFreq; f <= irMaxFreq; f += irFreqStep) {
    distance += irDetect(irLedPin, irReceivePin, f);
  }
  return distance;
}

// IR Detection function

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}    
