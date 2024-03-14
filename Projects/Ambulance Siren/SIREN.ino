const int PIN_RED =2;
const int PIN_GREEN = 3;
const int PIN_BLUE = 6;

int buzzerPin = 10;
int buttonPin = 13;
int ledState1 = 0;
int ledState2 = 0;
int ledState3 = 0;
int buttonState = 0;
int flash = 0;
unsigned long int flashmillis = 0;
int flash_toggle = 1;



void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void flashColors(int flash) {
  if (flash == 1) {
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, HIGH);
  } else if (flash == 2) {
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, HIGH);
  } else if (flash == 3) {
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, HIGH);
  } else
   {
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE, LOW);
  } 
}

void loop() {


  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    while (buttonState == HIGH) {
      buttonState = digitalRead(buttonPin);
    }

    if ((ledState1 == 0) && (ledState2 == 0) && (ledState3 == 0)) {
      digitalWrite(PIN_RED, HIGH);
      digitalWrite(PIN_GREEN, HIGH);
      digitalWrite(PIN_BLUE, HIGH);
      tone(buzzerPin, 440);
      flash = 1;
      ledState1 = 1;
      ledState2 = 1;
      ledState3 = 1;
      flashmillis = millis();
    } else {
      digitalWrite(PIN_RED, 0);
      digitalWrite(PIN_GREEN, 0);
      digitalWrite(PIN_BLUE, 0);
      flash = 0;
      ledState1 = 0;
      ledState2 = 0;
      ledState3 = 0;
      noTone(buzzerPin);
    }
  }
  if (flash == 1) {
    if (millis() - flashmillis > 500) {
      flash_toggle++;
      if (flash_toggle > 4)
      {
        flash_toggle=1;
      }
      flashColors(flash_toggle);
      flashmillis = millis();
    }
  }
}
