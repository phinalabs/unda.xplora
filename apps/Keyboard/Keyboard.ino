/*
* Lesson 3: Tri-Color LED
* (c) 2023 phinalabs
* License: MIT
*/

//button pin
#define BUTTON_1 7
#define BUTTON_2 8
#define BUTTON_3 9
#define BUTTON_4 10

typedef enum{
  U = 0xDA, //UP
  D = 0xD9, //DOWN
  N= 0xD8, //LEFT
  A = 0xD7, //RIGHT
  BACKSPACE = 0xB2, //BACKSPACE
  RETURN = 0xB0, //ESCAPE
  DELETE = 0xD4, //DELETE
  TAB = 0xB3, //TAB
  CAPS = 0xC1 //CAPS LOCK
} keys_t;

//state
typedef enum {
  OFF = 0,  //device powered on
  ON       //device ready
} state_t;

//private variables
int cur_state = -1;
long int prev_millis = 0;
int debounce_time = 200;

void sendChar(uint8_t sel) {
  //start
  Serial.write(0xC9);
  //send key
  Serial.write(sel); 
  //end
  Serial.write(0xCC);
  //reset timeout
  prev_millis = millis();
}


//function to handle button press
void ledStateHandler() {
  int button1_pressed = 0;
  int button2_pressed = 0;
  int button3_pressed = 0;
  int button4_pressed = 0;
  //create a timeout for button press
  if ((millis() - prev_millis) > debounce_time) {
    //read button
    button1_pressed = digitalRead(BUTTON_1);
    button2_pressed = digitalRead(BUTTON_2);
    button3_pressed = digitalRead(BUTTON_3);
    button4_pressed = digitalRead(BUTTON_4);
    while(digitalRead(BUTTON_1) == 1){} //reject continous presses
    //set current runtime
    prev_millis = millis();
  }
  //check press
  if (button1_pressed) {
    sendChar(U);
    //reset press
    button1_pressed = 0;
  }
  //delay a little bit
  delay(10);
   if (button2_pressed) {
    sendChar(N);
    //reset press
    button2_pressed = 0;
  }
  //delay a little bit
  delay(10);
   if (button3_pressed) {
    sendChar(D);
    //reset press
    button3_pressed = 0;
  }
  //delay a little bit
  delay(10);
   if (button4_pressed) {
    sendChar(A);
    //reset press
    button4_pressed = 0;
  }
  //delay a little bit
  delay(10);
}

//run
void setup() {
  Serial.begin(57600);
  //set button as input
  
pinMode(BUTTON_1, INPUT);
pinMode(BUTTON_2, INPUT);
pinMode(BUTTON_3, INPUT);
pinMode(BUTTON_4, INPUT);
  //set as state off-default
  cur_state = OFF;
  //set current runtime
  prev_millis = millis();
}



void loop() {
  ledStateHandler();
}
