int irBeaconPin = A0;
float irBeaconValue, tmpSum, irBeaconMeanValue;
int nbrAvRuns = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irBeaconPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  irBeaconMeanValue = 0; tmpSum = 0;
  for (int k = 1; k<=nbrAvRuns; k++){
    irBeaconValue = digitalRead(irBeaconPin);
    //irBeaconValue = irBeaconValue*5/1024;
    tmpSum += irBeaconValue;
  };
  irBeaconMeanValue = tmpSum/nbrAvRuns;
  Serial.println(irBeaconMeanValue);
  delay(100);
}
