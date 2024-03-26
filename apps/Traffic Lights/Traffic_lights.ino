
/*
* Lesson 4: Traffic lights
* (c) 2023 phinalabs
* License: MIT
*/

#define RED_PIN 9
#define ORANGE_PIN 5
#define GREEN_PIN 2

//traffic lights colors
typedef enum {
  RED = 0,
  ORANGE,
  GREEN,
} colors_t;

//traffic state meaning
typedef enum {
  STOP = 0,
  READY_GO,
  GO,
  READY_STOP
} traffic_t;

//state and delays
const int states_times[4][2] = {
  { STOP, 5000 },
  { READY_GO, 3000 },
  { GO, 5000 },
  { READY_STOP, 2000 }
};

uint8_t state = 0;

//handler
void lightStateHandler() {
  switch (state) {
    case STOP:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(ORANGE_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      break;
    case READY_GO:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(ORANGE_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      break;
    case GO:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(ORANGE_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      break;
    case READY_STOP:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(ORANGE_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      break;
  }

  //wait for state
  int wait = states_times[state][1];
  delay(wait);

  //change state
  if (state >= 3) {
    state = 0;
  } else {
    state++;
  }
}

void setup() {
  //init LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(ORANGE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  lightStateHandler();
}
