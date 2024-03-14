const int button1Pin = 10;  // pushbutton 1 pin
const int button2Pin = 13;  // pushbutton 2 pin
const int ledPin = 2;       // LED pin

int led_state = 0;
int button1State = 0, button2State = 0;

int prev_btn1_state = -1;
int prev_btn2_state = -1;

long int prev_time = 0;

void setup() {

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (millis() - prev_time > 100) {
    button1State = digitalRead(button1Pin);
    button2State = digitalRead(button2Pin);
    prev_time = millis();
  }


  if ((button1State != prev_btn1_state) && (button1State == HIGH)) {
    while (button1State == HIGH) {
      button1State = digitalRead(button1Pin);
    }
    led_state = !led_state;
    digitalWrite(ledPin, led_state);
    prev_btn1_state = button1State;
    prev_time = millis();
  }

  if ((button2State != prev_btn2_state) && (button2State == HIGH)) {
    while (button2State == HIGH) {
      button2State = digitalRead(button2Pin);
    }
    led_state = !led_state;
    digitalWrite(ledPin, led_state);
    prev_btn2_state = button2State;
    prev_time = millis();
  }
  delay(10);
}
