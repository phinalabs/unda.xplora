#define MotorPin 10
#define Pot_Pin  A4

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
  pinMode(MotorPin, OUTPUT);

}

void loop() {
  int Pot_Value = analogRead(Pot_Pin);
  int speed = map(Pot_Value, 0, 1023, 0, 255);
  analogWrite(MotorPin, speed);
  if (Pot_Value<=200)
  {
    Pot_Value = 200;
  }
  int SpeedVal= map(Pot_Value,200,1023,0,100);
  sendValue(SpeedVal);

}
