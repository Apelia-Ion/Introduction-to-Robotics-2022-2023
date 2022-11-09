// declare all the joystick pins
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int segSize = 8; //nr de leduri

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;
const int g = 6;
const int dp = 7;

const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

int currentSegment = dp;
int nextSegment;

// modify if you have common anode
bool commonAnode = false; 

byte lastSwState = LOW;
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


int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte currentSegmentState = LOW;

//conform tabelului dat
int possibleTransitions[segSize][4] = {
  //UP DOWN LEFT RIGHT
  //-1 semnifica ca acea tranzitie nu e posibila (perete)
  { -1, g, f, b },    // A
  { a, g, f, -1 },    // B
  { g, d, e, dp },    // C  
  { g, -1, e, c },    // D
  { g, d, -1, c },    // E
  { a, g, -1, b },    // F
  { a, d, -1, -1 },   // G
  { -1, -1, c, -1 }   // DP
};

//retine configuratia afisajului 
byte segmentsState[segSize]={
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

//for the blinking segment
const unsigned long blinkTime = 300;
unsigned long lastBlinkTime = 0;

//Drawing states
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



void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
}

void loop() {
  if(currentState == 1)
  {
    blink();
    transition();
  }
  else
  {
    lightUpSegment();
  }

  buttonPress();
  changeState();


} 

//moving through segments in state 1
void transition() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  joyMoved = false;

  if (xValue > maxThreshold) {
    nextSegment = left;
    if(possibleTransitions[currentSegment][nextSegment] == -1)
    {
      nextSegment = currentSegment;
      joyMoved = false;
    }
    else{
      joyMoved = true;
    }
    
  }
  if (xValue< minThreshold) {
    nextSegment = right;
     if(possibleTransitions[currentSegment][nextSegment] == -1)
    {
      nextSegment = currentSegment;
      joyMoved = false;
    }
    else{
      joyMoved = true;
    }
  }
  if (yValue > maxThreshold) {
    nextSegment = up;
    if(possibleTransitions[currentSegment][nextSegment] == -1)
    {
      nextSegment = currentSegment;
      joyMoved = false;
    }
    else{
      joyMoved = true;
    }
  }
  if (yValue < minThreshold) {
    nextSegment = down;
     if(possibleTransitions[currentSegment][nextSegment] == -1)
    {
      nextSegment = currentSegment;
      joyMoved = false;
    }
    else{
      joyMoved = true;
    }
  }

  if (joyMoved != previousJoyMove) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    willTransition = joyMoved;
  }
  previousJoyMove = joyMoved;

  if (willTransition && !didTransition) {
    currentSegment = possibleTransitions[currentSegment][nextSegment];
  }
  didTransition = willTransition;
}

void blink() {
  for (int i = 0; i < segSize; ++i) {
    if (i == currentSegment) {
      continue;
    }
    digitalWrite(segments[i], segmentsState[i]);
  }
  if (millis() - lastBlinkTime > blinkTime) {
    digitalWrite(segments[currentSegment], currentSegmentState);
    lastBlinkTime = millis();
    currentSegmentState = !currentSegmentState;
  }
}


void buttonPress() {
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

bool longButtonPress(){
  longPress = false;
  if (millis() - pressedTime > resetTime)
    longPress = true;
  return longPress;
}

void changeState(){
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

void lightUpSegment() {
  xValue2 = analogRead(pinX);
  if (xValue2 > maxThreshold)
    segmentsState[currentSegment] = LOW;
  if (xValue2 < minThreshold)
    segmentsState[currentSegment] = HIGH;
  digitalWrite(segments[currentSegment], segmentsState[currentSegment]);
}

void reset() {
  for (int i = 0; i < segSize; ++i)
    segmentsState[i] = LOW;
  currentSegment = dp;
}

