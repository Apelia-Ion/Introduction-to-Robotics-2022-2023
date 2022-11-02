
#define NOTE_E1 41
#define NOTE_DS1 39
#define NOTE_C7 2093

// constante pt pini -> leduri, buzzer si buton
const int greenLedPinCar = 4;
const int yellowLedPinCar = 5;
const int redLedPinCar = 6;

const int redLedPinPedestrian = 7;
const int greenLedPinPedestrian = 8;

const int buttonPin = 2;
const int buzzerPin = 3;

//stari pt leduri, buton

byte greenLedCarState = HIGH;
byte yellowLedCarState = LOW;
byte redLedCarState = LOW;

byte redLedPedestrianState = HIGH;
byte greenLedPedestrianState = LOW;

byte buttonState = LOW;  //changed
byte reading = LOW;
byte lastReading = LOW;

//starile crosswalk-ului
const int state1 = 1; //satrea initiala rosu-pietoni, verde-masini 
const int state2 = 2; //galben-masini, rosu-pietoni, fara sunet
const int state3 = 3; //rosu-masini, verde-pietoni, beep
const int state4 = 4; //blinking veede-pietoni, rosu-masini, faster beep

int currentState = state1;
unsigned long stateStartTime = 0;

//Timpi pt stari
const int state1Time = 8000;
const int state2Time = 3000;
const int state3Time = 8000;
const int state4Time = 4000;

// for button debounce
bool pressedButton = false;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

//for buzzer
const int buzzerTone = 1000;
unsigned long buzzerTimeStamp = 0;
const int buzzerDuration = 200;
const int buzzerTimeState3 = 1000;
const int buzzerTimeState4 = 500;

//blink for state 4
const int blinkDuration = 500;



void setup() {
   
  pinMode(greenLedPinCar, OUTPUT);
  pinMode(yellowLedPinCar, OUTPUT);
  pinMode(redLedPinCar, OUTPUT);

  pinMode(redLedPinPedestrian, OUTPUT);
  pinMode(redLedPinPedestrian, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {

  debounce();
  if (pressedButton) {
   // Serial.println("press");
    switch (currentState) {
      case state1:
        fState1();
        break;
      case state2:
        fState2();
        break;
      case state3:
        fState3();
        break;
      case state4:
        fState4();
        break;
      default:
        break;
    }
  }
  updateSemaphors();

}

void debounce(){
  reading = digitalRead(buttonPin);

  if(reading != lastReading)
    {
      lastDebounceTime = millis();
    }
  if((millis()-lastDebounceTime) > debounceDelay) //daca am avut o apasare reala de buton
  {
    buttonState = reading;

    if(buttonState == LOW && currentState == state1 && !pressedButton)
    {
      stateStartTime = millis();
      //Serial.println("pressedButton");
      pressedButton = true;
    }

  }

  lastReading = reading; 
  
}


void updateSemaphors(){
  digitalWrite(greenLedPinCar, greenLedCarState);
  digitalWrite(yellowLedPinCar, yellowLedCarState);
  digitalWrite(redLedPinCar, redLedCarState);

  digitalWrite(redLedPinPedestrian, redLedPedestrianState);
  digitalWrite(greenLedPinPedestrian, greenLedPedestrianState);
}

void resetSemaphore(){  // aduce semaforul la satrea 1
  greenLedCarState = HIGH;
  yellowLedCarState = LOW;
  redLedCarState = LOW;

  redLedPedestrianState = HIGH;
  greenLedPedestrianState = LOW;
}

void fState1(){
  resetSemaphore();

  if (millis() - stateStartTime >= state1Time) 
  {
    currentState = state2;
    stateStartTime = millis();
  }
}

void fState2(){
  greenLedCarState = LOW;
  yellowLedCarState = HIGH;

  if (millis() - stateStartTime >= state2Time) 
  {
    currentState = state3;
    stateStartTime = millis();
  }
}

void fState3(){
  yellowLedCarState = LOW;
  redLedCarState = HIGH;

  redLedPedestrianState = LOW;
  greenLedPedestrianState = HIGH;

  if (millis() - buzzerTimeStamp >= buzzerTimeState3) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    buzzerTimeStamp = millis();
  }

  if (millis() - stateStartTime >= state3Time) 
  {
    currentState = state4;
    stateStartTime = millis();
  }
}

void fState4(){

  if (millis() - buzzerTimeStamp >= blinkDuration) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    greenLedPedestrianState = !greenLedPedestrianState;
    buzzerTimeStamp = millis();
  }

  if (millis() - stateStartTime >= state4Time) 
  {
    currentState = state1;
    pressedButton = false;
    resetSemaphore();
  }

}




