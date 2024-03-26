//define the LED pins
const led1Pin = 2
const led2Pin = 3
const led3Pin = 4

//define the potentiometer input pin
const int potPin = A0

//set up variables to pot value and voltage level
int potValue = 0
int voltageLevel = 0

// Function to light LEDs based on the potentiometer value
void lightLEDs() {
  if (voltageLevel == 0) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
  } else if (voltageLevel == 1) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, LOW);
  } else if (voltageLevel == 2) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
  }
}

void setup() {
  // Set LED pins as OUTPUT
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Initialize Serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read the value from the potentiometer
  potValue = analogRead(potentiometerPin);

  // Map the potentiometer value to 3 voltage levels (0, 1, 2)
  voltageLevel = map(potValue, 0, 1023, 0, 2);

  // Print the potentiometer value and voltage level (optional - for debugging)
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(", Voltage Level: ");
  Serial.println(voltageLevel);

  // Light the LEDs based on the voltage level
  lightLEDs();

  // Add a small delay to avoid rapid LED changes
  delay(100);
}
