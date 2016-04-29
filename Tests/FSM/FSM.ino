
const int buttonPin = 8;     // the number of the pushbutton pin
const int numberOfStates = 3;


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int currentState = numberOfStates - 1;
bool buttonPressed;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    buttonPressed = true;
  } else {
    if (buttonPressed) {
      currentState = (currentState + 1) % numberOfStates;
      buttonPressed = false;
      Serial.print("Pressed!");
      Serial.print("  ");
      Serial.println(currentState);
    } else {
      buttonPressed = false;
    }
  
  }
}
