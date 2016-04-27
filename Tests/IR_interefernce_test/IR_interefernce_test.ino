float tmpSum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tmpSum = 0;
  for (int k=1; k<=5; k++) {
    tone(4, 38000, 10);              // IRLED 38 kHz for at least 1 ms
    delay(1);                        // Wait 1 ms
    float ir = digitalRead(A0);
    tmpSum += ir;
  };
  Serial.println(tmpSum/5.0);
  delay(100);
}
