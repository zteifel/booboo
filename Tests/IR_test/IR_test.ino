    #include <Servo.h>          // Include servo library
    
    Servo servoLeft;
    Servo servoRight;
    int irLeft, irRight;
    int sumOnes = 0;
    int sumZeros = 0;
    
    void setup() {
      // put your setup code here, to run once:
    Serial.begin(9600);
      Serial.println("BooBoo initiated!"); 
      servoLeft.attach(13);
      servoRight.attach(12);
      tone(4, 2000,500);
      delay(1000);
      tone(4, 2000, 500);
    pinMode(10,INPUT);
    pinMode(9,OUTPUT);
    pinMode(3,INPUT);
    pinMode(2,OUTPUT);
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
      //tone(2, 38000, 8);                // IRLED 38 kHz for at least 1 ms
      //delay(1);
      //irRight = digitalRead(3);
      
      
      tone(9, 38000, 8);                // IRLED 38 kHz for at least 1 ms
      delay(1);                         // Wait 1 ms
      irLeft = digitalRead(10);         // IR receiver -> ir variable
      
      Serial.println(String(irLeft)+" "+String(irRight));
      
      if(irLeft == 1){
        sumOnes++;
        sumZeros = 0;
        }
      else{
        sumOnes = 0;
        sumZeros++;
      }
      
      if(sumOnes > 50){
        servoLeft.writeMicroseconds(1500);
        servoRight.writeMicroseconds(1500);
        }
      else if(sumZeros > 50){
        servoLeft.writeMicroseconds(1550);
        servoRight.writeMicroseconds(1450);
      }
      
      
    }
