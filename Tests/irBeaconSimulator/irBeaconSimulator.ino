int irLedPin = 2;
int frequency = 38000;
int simDelayLimit = 150;

void setup() {
  // put your setup code here, to run once:
pinMode(irLedPin, OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
    tone(irLedPin, frequency, 10);              // IRLED 37.5 kHz for at least 1 ms
    //digitalWrite(13,HIGH);
    noTone(irLedPin);
    //digitalWrite(13,LOW);
    //delay(simDelayLimit);
}
