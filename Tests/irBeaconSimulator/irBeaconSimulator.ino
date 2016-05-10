int irLedPin = 7;
int frequency = 37500;
int simDelayLimit = 150;

void setup() {
  // put your setup code here, to run once:
pinMode(irLedPin, OUTPUT);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    tone(irLedPin, frequency, 10);              // IRLED 37.5 kHz for at least 1 ms
    digitalWrite(13,HIGH);
    delay(simDelayLimit);
    digitalWrite(13,LOW);
    delay(simDelayLimit);
}
