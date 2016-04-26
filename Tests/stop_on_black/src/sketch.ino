
const int LIGHT_PIN     = 10;
const int READ_PIN      = 8;
const int INDICATOR_PIN = 12;

int reading;

void setup()
{
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(INDICATOR_PIN, OUTPUT);
  pinMode(READ_PIN,  INPUT);
  
  digitalWrite(LIGHT_PIN, HIGH);
  digitalWrite(INDICATOR_PIN, LOW);
  
  Serial.begin(9600);
}

void loop()
{
  reading = digitalRead(READ_PIN);  
  if(reading == HIGH){
    digitalWrite(INDICATOR_PIN, HIGH);
    Serial.println("HIGH");
  }else{
    digitalWrite(INDICATOR_PIN, LOW);
    Serial.println("LOW");
  }
  delay(500);
}
