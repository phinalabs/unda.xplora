/*
  Lesson 3: Tri-Color LED
  (c) 2023 phinalabs
  License: MIT
*/

//button pin
#define START_BUTTON 12
#define STOP_BUTTON 13

//state
typedef enum {
  RUN = 0,  //device powered on
  STOP,      //device ready
  PAUSE // pause
} state_t;

//private variables
int cur_state = -1;
long int prev_millis = 0;
int debounce_time = 100;

bool isRunning = false;


void sendCommand(uint8_t cmd) {
  Serial.write(0xc8);
  Serial.write(cmd);
  Serial.write('\r');
}

//function to handle button press
void ledStateHandler(int cmd) {
  int start_button_pressed = 0;
  int stop_button_pressed = 0;
  //create a timeout for button press
  if ((millis() - prev_millis) > debounce_time) {
    //read start button
    start_button_pressed = digitalRead(START_BUTTON);
    while (digitalRead(START_BUTTON) == 1) {}  //reject continous presses
    //read stop button
    //read button
    stop_button_pressed = digitalRead(STOP_BUTTON);
    while (digitalRead(STOP_BUTTON) == 1) {}  //reject continous presse
    //set current runtime
    prev_millis = millis();
  }

  //check if start button pressed
  if (start_button_pressed || cmd == 0x01) {
    start_button_pressed = 0;
    if(isRunning){
      cur_state = PAUSE;
      sendCommand(0x02);
      isRunning = false;
    }
    else{
      cur_state = RUN;
      sendCommand(0x01);
      isRunning = true;
    }
  }
  //check if stop button pressed
  if (stop_button_pressed || cmd == 0x00) {
    cur_state = STOP;
    stop_button_pressed = 0;
    sendCommand(0x00);
    isRunning = false;
  }
  //delay a little bit
  delay(1);
}

//run
void setup() {
  Serial.begin(57600);
  //set button as input
  pinMode(START_BUTTON, INPUT);
  pinMode(STOP_BUTTON, INPUT);
  //set as state off-default
  //speaker.begin(BUZZER);
  cur_state = STOP;
  //set current runtime
  prev_millis = millis();
}


void loop() {
  short cmd = -1;
  while (Serial.available() > 0) {
    cmd = (uint8_t)Serial.read();
  }
  ledStateHandler(cmd);
}
