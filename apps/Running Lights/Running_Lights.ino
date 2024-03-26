/**
 * Running Lights lesson for unda make
 * (c) phinalabs
 */
#define LEDS_NUM 5
#define SPEED 200

const int leds[LEDS_NUM] = { 3, 5, 6, 10, 11 };

int led_pos = 0;
int loc = 0;

void setup() {
  //serial begin
  Serial.begin(57600);
  // initialize digital pin LED1 as an output.
  for (int i = 0; i < LEDS_NUM; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  loop1();
}

/**
* scrolling leds - top to bottom
*/
void loop1() {
  for (int i = 0; i < LEDS_NUM; i++) {
    digitalWrite(leds[i], ((led_pos == i) ? HIGH : LOW));
  }

  if (loc == 0) {
    if (led_pos >= LEDS_NUM - 1) {
      loc = 1;
      led_pos--;
    } else led_pos++;
  } else if (loc == 1) {
    if (led_pos <= 0) {
      loc = 0;
      led_pos++;
    } else led_pos--;
  }
  //delay
  delay(SPEED);
}
