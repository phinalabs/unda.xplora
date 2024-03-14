
const int buttonPin = 2;
const int motorPin = 10;
int buttonState = 0;
//int prevButtonState = 0;
int motorState = 0;
//bool btnPressed = false;

void setup() {

  pinMode(motorPin, OUTPUT);

  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    while (buttonState == HIGH) 
    {
      buttonState = digitalRead(buttonPin);
    }

    if (motorState == 0) {
      digitalWrite(motorPin, HIGH);
      motorState = 1;
    } else {
      digitalWrite(motorPin, LOW);
      motorState = 0;
    }
  }

}
