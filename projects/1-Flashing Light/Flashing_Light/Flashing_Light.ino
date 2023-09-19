/*
* project: LED Blinking project for UNDA STEM Kit
* 
* (c) 2023 phinalabs
* License : MIT
*
*/

//led pin
const uint8_t LED_PIN = 2;

//modes
typedef enum {
  FAST_BLINK = 0x00,
  SLOW_BLINK,
  TICKER,
  HEARTBEAT,
  NOTIFY
} delay_mode_t;

delay_mode_t mode = TICKER;
uint8_t toggle_state = 0;
//setup
void setup() {
  //set serial baud rate
  Serial.begin(57600);
  //set led pn as output
  pinMode(LED_PIN, OUTPUT);
}

//loop
void loop() {
  //check if a command is available
  if (Serial.available() > 0) {
    //read a byte from serial
    uint8_t cmd = (uint8_t)Serial.read();
    //save command
    mode = cmd;
    //clear serial tx/rx buffer
    Serial.flush();
  }
  //run diffrent modes
  switch (mode) {
    //blink fast-100ms
    case FAST_BLINK:
      digitalWrite(LED_PIN, toggle_state);
      delay(100);
      toggle_state = !toggle_state;
      break;
      //blink slowly-3000ms
    case SLOW_BLINK:
      digitalWrite(LED_PIN, toggle_state);
      delay(3000);
      toggle_state = !toggle_state;
      break;
      //time tick- 500ms toggle state
    case TICKER:
      digitalWrite(LED_PIN, toggle_state);
      delay(500);
      toggle_state = !toggle_state;
      break;
      //pulsating
    case HEARTBEAT:
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(1000);
      break;
      //fast blink 3 times then off for some period
    case NOTIFY:
      for (int i = 0; i < 6; i++) {  //fast blink 3 times
        digitalWrite(LED_PIN, toggle_state);
        delay(200);
        toggle_state = !toggle_state;
      }
      digitalWrite(LED_PIN, LOW);
      delay(1000);
      break;
    default: break;
  }
}
