//LIBRARIES
#include <LiquidCrystal.h>
#include "LedControl.h" 
#include <EEPROM.h>

//JOYSTICK
const int xPin = A0;
const int yPin = A1;
const int pinSW = 2;

bool joyMoved = false;
bool previousJoyMove = false;

bool didTransition = false;
bool willTransition = false;

int swState = LOW;  //button state
int lastSwState = HIGH;  //last button state
int switchValue;
int xValue = 0;
int yValue = 0;

//for debounce
unsigned long lastDebounceTime = 0;  //for scrolling
const unsigned long debounceDelay = 100;

//for joystick button press
byte press = LOW;  //press state

bool buttonPressed = false;
bool shortPress = false;
bool longPress = false;
//unsigned long pressedTime = 0;
unsigned long buttonDebounceTime = 0;
//unsigned long pressedDebounceTime = 0;
//unsigned long releasedDebounceTime = 0;

//LCD
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//MATRIX
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER

byte matrixBrightness = 4;
const byte matrixSize = 8;

byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}  
};

//


//GAME 
byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;

const int minThreshold = 400;
const int maxThreshold = 600;

const byte moveInterval = 100;
unsigned long long lastMoved = 0;

bool matrixChanged = true;

struct highscores{
  char name[10] = "Unknown";
  unsigned int score = 0;
};

const unsigned int hsAddress[] = {967, 978, 989, 1000, 1012};

//MENU
int mainMenu = 0;

unsigned long greetingTime = 5000;
bool clear = 0;
unsigned long startTime = 0;
unsigned long currentTime ;
int page = 0;
bool action = false;

byte upArrow[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000
};

byte downArrow[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000
};



unsigned long lastPrint = 0;
unsigned long lastTime;


void setup() {

  
  pinMode(pinSW, INPUT_PULLUP); 

  
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  matrix[xPos][yPos] = 1;
 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);

  initializeHighScoreEeprom();

 Serial.begin(9600);

 
}



void loop() {
  Welcome();
  
  
     
}

// theoretical example
void generateFood() {
  // lastFoodPos = currentPos;
  // newFoodPos = random(ceva);
  // matrix[lastFoodPos] = 0;
  // matrix[newFoodPos] = 1;
  matrixChanged = true;
}

void updateMatrix() {
 // TODO: update matrix using byte matrix (refresh function)
   for(int i = 0; i<matrixSize; i++) 
   {
     for (int j = 0; j<matrixSize; j++) 
     {
       lc.setLed(0,i,j,matrix[i][j]);
     }
   }
}

void updatePositions() {
 // TODO: joystick control
 int xValue = analogRead(xPin);
 int yValue = analogRead(yPin);
 
 xLastPos = xPos;
 yLastPos = yPos;
 if (xValue < minThreshold) 
 {
   if (xPos > 0) 
    {
      xPos--;
    }
    else 
    {
      xPos = matrixSize - 1;
    }
 }

 if (xValue > maxThreshold) 
 {
   if (xPos < (matrixSize - 1)) 
   {
      xPos++;
    } 
    else 
    {
      xPos = 0;
    }
 }


  if (yValue > maxThreshold) 
  {
    if (yPos < (matrixSize - 1)) 
    {
      yPos++;
    } 
    else 
    {
      yPos = 0;
    }
  }

  if (yValue < minThreshold) 
  {
    if (yPos > 0) 
    {
      yPos--;
    }
    else 
    {
      yPos = matrixSize - 1;
    }
  }

  if (xLastPos != xPos || yLastPos != yPos) 
  {
  matrix[xLastPos][yLastPos] = 0;
  matrix[xPos][yPos]=1;
  matrixChanged = true;
  lastMoved = millis();
  }

}

void rudimentaryGame(){
   if(millis() - lastMoved > moveInterval) 
  {
    updatePositions(); // calculare stare
  }

  if(matrixChanged == true) 
  {
    updateMatrix();
    matrixChanged = false;
  }
}
///////////////////////////////////////////// Functions for GAME MENU /////////////////////////////////////////////

//0 - Clear text by overwriting it with padding - prevents flickering
void paddingClear(){
  lcd.setCursor(0, 0);
  lcd.print("                "); 
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

//1 - Welcome message - displays welcomeing message for 5 seconds, then clears the lcd and displays the menu
void Welcome(){
  if (millis() <= greetingTime)
  //if (currentTime - startTime <= 5000)
  {
    lcd.setCursor(0, 0);
    lcd.print("Hi there gamer!");
    lcd.setCursor(0, 1);
    lcd.print("      ^-^      ");  
  }
  else
  {
    if (!clear) {
      lcd.clear();
      clear = 1;
    }

   switch(mainMenu){
     case 0:
     {
      buttonPressed = false;
      
      page = pagesScroll();
      Menu(page);
      buttonPress();
      if (buttonPressed == true)
      {
        mainMenu = 1;
      }       
     }
     break;

     case 1:
     {
       SubMenu(page);
       buttonPress();
      if (buttonPressed == true)
      {
        mainMenu = 0;
        clear = 0;
      }       
     }
     break;

   } 
  
  }
  
}

//2 function that allows to scroll through the menu options
int pagesScroll(){
 
      yValue = analogRead(yPin);

    joyMoved = false;

    int nextPage = 0;

    if (yValue > maxThreshold) 
    {
      
      if(page > 0)
      {
        //lcd.clear();
        nextPage = page - 1;
        joyMoved = true;
      }
      else
      {
        nextPage = page;
        joyMoved = false;
      }
    }

    if (yValue< minThreshold) 
    {
      
      if(page < 4)
      {
        //lcd.clear();
        nextPage = page + 1;
        joyMoved = true;
      }
      else
      {
        nextPage = page;
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
      page = nextPage;
      lcd.clear();
    }

    didTransition = willTransition;

    return page;   
  
}  

// 3 - function that displays the menu options
void Menu(int page){
  switch (page) {
   
    case 0:{     //Page 0
      lcd.setCursor(0,0);
      lcd.print(">");
      lcd.setCursor(2,0);
      lcd.print("START GAME");
      lcd.setCursor(2,1);
      lcd.print("Highscore");
      lcd.setCursor(15,1);
      lcd.write(byte(1));
    }
    break;

    case 1:{     //Page 1
      lcd.setCursor(0,0);
      lcd.print(">");
      lcd.setCursor(2,0);
      lcd.print("Highscore");
      lcd.setCursor(2,1);
      lcd.print("Settings");
      lcd.setCursor(15,0);
      lcd.write(byte(0));
      lcd.setCursor(15,1);
      lcd.write(byte(1));

    }
    break;

    case 2: { //Page 2 
     lcd.setCursor(0,0);
     lcd.print(">");
     lcd.setCursor(2,0);
     lcd.print("Settings");
     lcd.setCursor(2,1);
     lcd.print("About");
     lcd.setCursor(15,0);
     lcd.write(byte(0));
     lcd.setCursor(15,1);
     lcd.write(byte(1)); 
    
    }
    break;

    case 3: {   //Page 3
     lcd.setCursor(0,0);
     lcd.print(">");
     lcd.setCursor(2,0);
     lcd.print("About");
     lcd.setCursor(2,1);
     lcd.print("How to play");
     lcd.setCursor(15,0);
     lcd.write(byte(0));
     lcd.setCursor(15,1);
     lcd.write(byte(1));
    
    }
    break;

    case 4: {   //Page 4
     lcd.setCursor(0,0);
     lcd.print(">");
     lcd.setCursor(2,0);
     lcd.print("How to play");
     lcd.setCursor(15,0);
     lcd.write(byte(0));
    
    }
    break;
  }
      
}

void buttonPress() {
  press = digitalRead(pinSW);
  if (press != lastSwState) 
  {
    buttonDebounceTime = millis();
  }
  if(millis()- buttonDebounceTime > debounceDelay)
  {
    if(press != swState)
    {
      swState = press;
      if(swState == LOW)
      {
        buttonPressed = true;
      }
    }

  }
  lastSwState = press;
}


void SubMenu(int page){
  

  if(buttonPressed)
  {
    Serial.println(buttonPressed);

    lcd.clear();
    switch (page) 
    {
   
      case 0:{     //Page 0
        lcd.setCursor(0,0);
        lcd.print("U are playing");
        rudimentaryGame();

      }
      break;

      case 1:{     //Page 1
        lcd.setCursor(0,0);
        lcd.print("Highscore");
        highscore();

      }
      break;

      case 2: { //Page 2 
      lcd.setCursor(0,0);
      lcd.print("Settings");
      }
      break;

      case 3: {   //Page 3
      lcd.setCursor(0,0);
      lcd.print("About");
      }
      break;

      case 4: {   //Page 4
      lcd.setCursor(0,0);
      lcd.print("How to play");
      }
      break;
    }
  

  }

   buttonPressed = false;
}

void initializeHighScoreEeprom() {
  highscores highscores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.put(hsAddress[i], highscores[i]);
  }
}

void highscore(){
   highscores highscores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.get(hsAddress[i], highscores[i]);
    lcd.setCursor(0, 1);
    lcd.print((int) i+1);
    lcd.setCursor(1, 1);
    lcd.print(highscores[i].name);
    lcd.setCursor(11, 1);
    lcd.print(highscores[i].score);
    delay(500);
  }


}



