#define LED 3
#define POT_PIN A7

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


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(57600);

}

void loop() {
int Pot_Value =analogRead(POT_PIN);
int brightness = map(Pot_Value, 0, 1023,0,100);
analogWrite(LED, brightness);
sendValue(brightness);

}
