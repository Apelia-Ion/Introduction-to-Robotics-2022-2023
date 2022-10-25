const int maxAnalogValue = 1023;
const int minAnalogValue = 0;
const int maxDutyCycle = 255;
const int minDutyCycle = 0;

const int potLedRed = A0;
const int potLedGreen = A1;
const int potLedBlue = A2;

const int pinLedRed = 11;
const int pinLedGreen = 10;
const int pinLedBlue = 9;

int ledValueRed;
int ledValueGreen;
int ledValueBlue;

int potValueRed;
int potValueGreen;
int potValueBlue;

void setLedColor(int red, int green, int blue) {

  analogWrite(pinLedRed, red);
  analogWrite(pinLedGreen, green);
  analogWrite(pinLedBlue, blue);
  
}

void printLedValues(int red, int green, int blue) {

  Serial.print("R: ");
  Serial.print(red);
  Serial.print("G: ");
  Serial.print(green);
  Serial.print("B: ");
  Serial.println(blue);

}

void setup() {
  
  pinMode(potLedRed, INPUT);
  pinMode(potLedGreen, INPUT);
  pinMode(potLedBlue, INPUT);
  
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedBlue, OUTPUT);

  Serial.begin(9600); 

}

void loop() {
  
  potValueRed = analogRead(pinLedRed);
  potValueGreen = analogRead(pinLedGreen);
  potValueBlue = analogRead(pinLedBlue);

  ledValueRed = map(potValueRed, minAnalogValue, maxAnalogValue, minDutyCycle, maxDutyCycle);
  ledValueGreen = map(potValueGreen, minAnalogValue, maxAnalogValue, minDutyCycle, maxDutyCycle);
  ledValueBlue = map(potValueBlue, minAnalogValue, maxAnalogValue, minDutyCycle, maxDutyCycle);

  printLedValues(ledValueRed, ledValueGreen, ledValueBlue);

  setLedColor(ledValueRed, ledValueGreen, ledValueBlue);

}
