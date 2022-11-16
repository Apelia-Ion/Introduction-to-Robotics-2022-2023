//joystick
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const byte regSize = 8; // 1 byte aka 8 bits

int displays[] =
 {
  segD1, segD2, segD3, segD4
 };

const int displayCount = 4;
int currentDisplay = 0;
int nextDisplay = 0;

byte registers[regSize];

const int encodingsNumber = 16;

byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};


int dpState = HIGH;
int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;
int xValue2 = 0;

//for transitions
bool joyMoved = false;
bool previousJoyMove = false;

bool didTransition = false;
bool willTransition = false;

int minThreshold = 400;
int maxThreshold = 600;

//for debounce
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100;


int currentDigit = 0;
int valueD1 = 0;
int valueD2 = 0;
int valueD3 = 0;
int valueD4 = 0;

int values[displayCount] = {
 valueD1, valueD2, valueD3, valueD4  
};


const unsigned long blinkTime = 500;
unsigned long lastBlinkTime = 0;

const int state1 = 1;
const int state2 = 2;
int currentState = 1;

//Button press
byte press = LOW;

bool buttonPressed = false;
bool shortPress = false;
bool longPress = false;
unsigned long pressedTime = 0;

const unsigned long resetTime = 3000;
unsigned long pressedDebounceTime = 0;
unsigned long releasedDebounceTime = 0;

// debounce + for incrementing once for each y axis move
unsigned long ChangeDebounceTime = 0;
const unsigned long ChangeDebounceDelay = 300;\
bool changed = false;
bool previousChange = false;

bool didIncrement= false;
bool willIncrement = false;


void activateDisplay(int displayNumber) {

  for (auto display:displays) {
    digitalWrite(display, HIGH);
  }

  digitalWrite(displays[displayNumber], LOW);
}

void writeReg(byte encoding) 
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

//moving through segments in state 1
void transition() 
{
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  joyMoved = false;

  if (xValue > maxThreshold) 
  {
    if(currentDisplay > 0)
    {
      nextDisplay = currentDisplay - 1;
      joyMoved = true;
    }
    else
    {
      nextDisplay = currentDisplay;
      joyMoved = false;
    }
  }

  if (xValue< minThreshold) 
  {
    if(currentDisplay < 3)
    {
      nextDisplay = currentDisplay + 1;
      joyMoved = true;
    }
    else
    {
      nextDisplay = currentDisplay;
      joyMoved = false;
    }
  }

  if (joyMoved != previousJoyMove) 
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    willTransition = joyMoved;
  }

  previousJoyMove = joyMoved;

  if (willTransition && !didTransition) 
  {
    currentDisplay = nextDisplay;
  }

  didTransition = willTransition;
}  


void blink() 
{
  for (int i = 0; i < displayCount; ++i) 
  {
    if (i == currentDisplay) 
    {
      continue;
    }
  }

  writeReg(B00000000);
  activateDisplay(currentDisplay);

  if (millis() - lastBlinkTime > blinkTime) 
  {
    //writeReg(B00000001);
    lastBlinkTime = millis();
    writeReg(B00000001);
    activateDisplay(currentDisplay);
    //
  }

}

void buttonPress() 
{
  press = digitalRead(pinSW);
  if (!press) 
  {
    if (millis() - pressedDebounceTime > debounceDelay) 
    {
      buttonPressed = true;
      shortPress = false;
      pressedTime = millis();
    }
    pressedDebounceTime = millis();
  } 
  else 
  {
    if (millis() - releasedDebounceTime > debounceDelay) {
      shortPress = true;
    }
    releasedDebounceTime = millis();
  }

}

bool longButtonPress()
{
  longPress = false;
  if (millis() - pressedTime > resetTime)
    longPress = true;
  return longPress;
}

void reset() 
{
  for (int i=0; i< displayCount; i++)
  {
    
    writeReg(B00000000);
    activateDisplay(i);
    values[i]= 0;
  }
  currentDisplay = 0;
  currentState = 1;
}


void changeState()
{
  if (buttonPressed) 
  {
    if (shortPress) 
    {
      if (currentState == state1) 
      {
        currentState = state2;
        buttonPressed = false;
      } 
      else 
      {
        currentState = state1;
        buttonPressed = false;
      }
    }
    else if (currentState == state1)
    {
      if(longButtonPress())
      {
        buttonPressed = false;
        reset();
      }

    }
    else
    {
      shortPress = false;
    }
  }

}


void changeDisplayValue() 
{

  if (currentState == 2)
  {
    
    if(millis() - ChangeDebounceTime > ChangeDebounceDelay)
    {
      yValue = analogRead(pinY);
      currentDigit = values[currentDisplay];
      changed = false;

      if (yValue > maxThreshold && currentDigit < 15  ) 
      {
       currentDigit += 1;
       //values[currentDisplay]= currentDigit;
       changed = true;
      
      }
   
      if (yValue < minThreshold && currentDigit > 0 )
      {
        currentDigit -= 1;
        //values[currentDisplay]= currentDigit;
        changed = true;
      }
      ChangeDebounceTime = millis();
    }

      if (changed != previousChange) 
      {
        lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay) 
      {
        willIncrement = changed;
      }

      previousChange = changed;

      if (willIncrement && !didIncrement) 
      {
        values[currentDisplay]= currentDigit;
      }

      didIncrement = willIncrement;
    
  }

}

void blacken()
{
  for (int i=0; i< displayCount; i++)
  {
    writeReg(B00000000);
    activateDisplay(i);
  }
}

void lightUp()
{
  for (int i=0; i< displayCount; i++)
  {

    blacken();

    if(i == currentDisplay && currentState == state2)
    {
      activateDisplay(i);
      writeReg(B00000001);
      writeReg(byteEncodings[values[i]]);
    }

    if(i == currentDisplay && currentState == state1)
    {
      activateDisplay(i);
      writeReg(byteEncodings[values[i]]);
    }

    else
    {
      activateDisplay(i);
      writeReg(byteEncodings[values[i]]);
    }
  }
}



void setup()
 {
  // initialize all the pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); //
  pinMode(dataPin, OUTPUT); //ds

  pinMode(pinSW, INPUT_PULLUP);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displays[i], OUTPUT);
    digitalWrite(displays[i], LOW);
  }
  Serial.begin(9600);
}




void loop() 
{
  
  if(currentState == 1)
  {
    blacken();
    lightUp();
    blink();
    transition();
    
    
    
  }
   else
  {
    
    changeDisplayValue();
    blacken();
    lightUp();
  }

 
  
  buttonPress();
  changeState();
}