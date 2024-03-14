//set pin numbers
//const won't change
const int ledPin = 2;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin


void setup() {

  Serial.begin(57600);
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
}

void loop() {

  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

   if (ldrStatus <=300) {

    digitalWrite(ledPin, HIGH);               //turn LED on
    Serial.println("LDR is DARK, LED is ON");
    sendChar('LDR is DARK, LED is ON');
    
   }
  else {

    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("---------------");
    sendChar('LDR is BRIGHT, LED is OFF');
  }
}

void sendChar(char Ch)
{
     Serial.write(0XC9);
     Serial.write(Ch);
     Serial.write(0XCC);


}