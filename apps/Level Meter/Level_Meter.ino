/*
* 3 Point level meter
* (c) 2023 https://phinalabs.com
*
* ----- components -----
* 1 | Potentiometer
* 2 | LEDS - Green, Orange, Red
* 3 | Jumpers
* 
* ----- pinouts -----
* A0 | Potentiometer output
* D3 | LED Green
* D4 | LED Orange
* D5 | LED Red
* -------------------
*/

//potentiometer pin
#define POT_PIN A0
//green pin
#define LED_GREEN_PIN 4
//orange pin
#define LED_ORANGE_PIN 5
//red pin
#define LED_RED_PIN 6

//levels - 3 point
enum LEVELS {
  LEVEL_MIN = 1,  //minimum
  LEVEL_MID,      //middle
  LEVEL_MAX       //maximum
};

//wait time to send commands
const int wait_delay = 500;
//variable to hold previous time
unsigned long int previous_millis = 0;

//send function handler
void sendValue(uint16_t value) {
  //send start command
  Serial.write(0xc8);
  //send LSB
  Serial.write((value & 0xff));
  //send MSB
  Serial.write(((value >> 8) & 0xff));
  //end command
  Serial.write('\r');
}

//return a level point between 1-3
uint8_t getLevel(uint16_t value) {  //min
  if (value >= 0 && value <= 341) {
    return LEVEL_MIN;
  } else if (value > 341 && value <= 682) {  //mid
    return LEVEL_MID;
  } else {  //max
    return LEVEL_MAX;
  }
}

//set LED level
void setLedLevel(uint8_t level) {
  //set all leds off
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_ORANGE_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  //set level led
  switch (level) {
    case LEVEL_MIN:  //minimum
      digitalWrite(LED_GREEN_PIN, HIGH);
      break;
    case LEVEL_MID:  //middle
      digitalWrite(LED_ORANGE_PIN, HIGH);
      break;
    case LEVEL_MAX:  //maximum
      digitalWrite(LED_RED_PIN, HIGH);
      break;
    default: break;
  };
}

//setup
void setup() {
  Serial.begin(57600);
  //set LED pins as outputs
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_ORANGE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
}

//loop
void loop() {
  //read analog value from the potentiometer
  uint16_t value = analogRead(POT_PIN);
  //get level
  uint8_t level = getLevel(value);
  //set level
  setLedLevel(level);
  //send to display after wait time
  if ((millis() - previous_millis) > wait_delay) {
    //map analog to level values
    int value_percent = map(value, 0, 1023, 0, 100);
    //send to display
    sendValue(value_percent);
    //set previous wait time
    previous_millis = millis();
  }
  //delay a little bit
  delay(20);
}
