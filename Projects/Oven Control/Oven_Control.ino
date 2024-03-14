#define sensorPin A1
#define greenLED 3
#define redLED 2

void setup() {
  Serial.begin(57600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
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
  if (temperatureC >= 0 && (temperatureC <= 28)) {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);

  } else {
    digitalWrite(greenLED, HIGH;
    digitalWrite(redLED, LOW);
  }

  delay(3000);
}
