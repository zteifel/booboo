int irBeaconPinLeft  = A0;
int irBeaconPinRight = A1;
float irBeaconLeftVal, irBeaconRightVal, tmpSum, irBeaconMeanValue;
int nbrAvRuns = 1;

void setup() {
  Serial.begin(9600);
  pinMode(irBeaconPinLeft, INPUT);
  pinMode(irBeaconPinRight,INPUT);
}

void loop() {
  int tmpSumLeft = 0;
  int tmpSumRight = 0;
  for (int k = 1; k<=nbrAvRuns; k++){
    irBeaconLeftVal = analogRead(irBeaconPinLeft)*5.0/1024.0;  
    irBeaconRightVal = analogRead(irBeaconPinRight)*5.0/1024.0;
    //irBeaconValue = irBeaconValue*5/1024;
    tmpSumLeft  += irBeaconLeftVal;
    tmpSumRight += irBeaconRightVal;
  };
  int irBeaconMeanLeft  = tmpSumLeft/nbrAvRuns;
  int irBeaconMeanRight = tmpSumRight/nbrAvRuns;
  Serial.println(
    "Left: "  + String(irBeaconMeanLeft) + "\t" +
    "Right: " + String(irBeaconMeanRight)
  );
  delay(100);
}
