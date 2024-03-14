#define sensorPin A6
#define ldrPin A0

int prev_Millis = 0;

void setup()
{
  Serial.begin(57600);
  pinMode(sensorPin, INPUT);
  pinMode(ldrPin, INPUT);
}
void sendValue(uint16_t value)
{
  // send start command
  Serial.write(0xc8);
  // send LSB
  Serial.write((value & 0xff));
  // send MSB
  Serial.write(((value >> 8) & 0xff));
  // end command
  Serial.write('\r');
}
void loop()
{

  unsigned long currentMillis = millis();
  int temperatureC = 0;
  if (currentMillis - prev_Millis > 500)
  {
    prev_Millis = currentMillis;
    int temp_reading = analogRead(sensorPin);
    float voltage = int(temp_reading * 5.0) / 1024.0;
    temperatureC = int((voltage - 0.5) * 100);
  }

  int ldrstatus = analogRead(ldrPin);
  int brightness = map(ldrstatus, 0, 1023, 0, 100);

  int sensor = ((temperatureC << 8) | (brightness));
  sendValue(sensor);
  delay(200);
}
