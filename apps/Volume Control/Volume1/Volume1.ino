#define BUZZER 11
#define POT_PIN A3


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
  Serial.begin(57600);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
  int Pot_Value =analogRead(POT_PIN);
  int volume = map(Pot_Value, 0,1023,0,100);
  analogWrite(BUZZER, volume);
  sendValue(volume);
  delay(100);
  }

