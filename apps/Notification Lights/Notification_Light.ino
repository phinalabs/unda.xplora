/*
* Lesson 3: Tri-Color LED
* (c) 2023 phinalabs
* License: MIT
*/

#define NUM_COLORS 7
#define WAIT 1000

//pins
#define RED_PIN 2
#define GREEN_PIN 4
#define BLUE_PIN 6
//button pin
#define BUTTON 10

//colors
typedef enum {
  RED = 0,
  GREEN
} colors_t;

//state
typedef enum {
  POWER = 0,  //device powered on
  READY       //device ready
} state_t;

//private variables
int cur_state = -1;
long int prev_millis = 0;
int debounce_time = 200;

//function to handle button press
void notifyStateHandler() {
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
    if (cur_state == POWER) {  //power -> ready
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      cur_state = READY;
    } else if (cur_state == READY) {  //ready -> power
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(RED_PIN, HIGH);
      cur_state = POWER;
    }
    //reset press
    button_pressed = 0;
  }
  //delay a little bit
  delay(10);
}

//run
void setup() {
  //set LEDs as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  //set button as input
  pinMode(BUTTON, INPUT);
  //set as power-default
  digitalWrite(RED_PIN, HIGH);
  cur_state = POWER;
  //set current runtime
  prev_millis = millis();
}


void loop() {
  notifyStateHandler();
}
