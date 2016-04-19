int irLedPin = 7;
int irRecPin = 2;
int statusLedPin = 13;
int frequency = 37500;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  pinMode(irLedPin, OUTPUT);
  pinMode(statusLedPin, OUTPUT);
  pinMode(irRecPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  if(random() < 0.5) {
    digitalWrite(statusLedPin, HIGH);
    tone(irLedPin, frequency, 10);              // IRLED 37.5 kHz for at least 1 ms
    delay(1);
  };
  
  float irVal = digitalRead(irRecPin);
  Serial.println(irVal);
  digitalWrite(statusLedPin, LOW);
  delay(1);
  
}
