#define sensorPin A5


void setup() {
  Serial.begin(57600);
  pinMode(sensorPin, INPUT);
}
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
void loop() {
  int temp_reading = analogRead(sensorPin);

  float voltage = int(temp_reading * 5.0) / 1024.0;
  int temperatureC = int((voltage - 0.5) * 100);
  sendValue(int(temperatureC));
  delay(3000);
}
