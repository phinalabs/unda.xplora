/*
* Lesson 3: Tri-Color LED
* (c) 2023 phinalabs
* License: MIT
*/

//pins
#define LED_PIN 4
//button pin
#define BUTTON 10

//state
typedef enum {
  OFF = 0,  //device powered on
  ON       //device ready
} state_t;

//private variables
int cur_state = -1;
long int prev_millis = 0;
int debounce_time = 200;

//function to handle button press
void ledStateHandler() {
  int button_pressed = 0;
  //create a timeout for button press
  if ((millis() - prev_millis) > debounce_time) {
    //read button
    button_pressed = digitalRead(BUTTON);
    while(digitalRead(BUTTON) == 1){} //reject continous presses
    //set current runtime
    prev_millis = millis();
  }
  //check press
  if (button_pressed) {
    if (cur_state == OFF) {  //power -> ready
      digitalWrite(LED_PIN, HIGH);
      cur_state = ON;
    } else if (cur_state == ON) {  //ready -> power
      digitalWrite(LED_PIN, LOW);
      cur_state = OFF;
    }
    //reset press
    button_pressed = 0;
  }
  //delay a little bit
  delay(10);
}

//run
void setup() {
  //set LED as outputs
  pinMode(LED_PIN, OUTPUT);
  //set button as input
  pinMode(BUTTON, INPUT);
  //set as state off-default
  digitalWrite(LED_PIN, LOW);
  cur_state = OFF;
  //set current runtime
  prev_millis = millis();
}


void loop() {
  ledStateHandler();
}
