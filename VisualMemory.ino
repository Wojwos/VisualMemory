#include <LiquidCrystal.h>

#include <FastLED.h>


#include <Keypad.h>

//LED
#define NUM_LEDS 72
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

//LCD
const int rs = 0, rw = 1, e=2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, rw, e, d4, d5, d6, d7);

//KEYPAD
const byte rows = 6; //six rows
const byte cols = 6; //six columns
char keys[rows][cols] = {
  {'1','2','3','4','5','6'},
  {'7','8','9','0','A','B'},
  {'C','D','E','F','G','H'},
  {'I','J','K','L','M','N'},
  {'O','P','R','S','T','W'},
  {'!','@','#','$','%','^'}
};
byte rowPins[rows] = {A5, A4, A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[cols] = {8, 9, 10, 11, 12, 13}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

//variables
int selectRandom = 1;
int n = 1;
int level = 1;
int count = 5;
bool gameMap[36] = {0};
int state = 0;
int lives = 3;
int guessed = 0;

void setup() {
  randomSeed(analogRead(A0));
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  lcd.begin(16, 2);
  keypad.addEventListener(keypadEvent);
}

void loop() {
  lives = 3;
  count = 5;
  while(lives > 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nacisnij dowolny");
    lcd.setCursor(0, 1);
    lcd.print("przycisk!");
    lcd.print("Poziom");
    lcd.print(count-4);
    char key = keypad.waitForKey();
    for (int i = 0; i < 36; i++) {
      gameMap[i]=0;
    }
    if(state==0)
      startState();
    if(state==1)
      guessState();
    if(state==2)
      winState();
  }
}

void startState(){
  lives=3;
  state=0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zapamietaj pola!");
  delay(3000);
  for (int i = 0; i < count; i++) {
    n = random(0, 36);
    if(gameMap[n] == 0){
      gameMap[n] = 1;
    }
    else{
      while(gameMap[n] != 0){
        n = random(0, 36);
      }
      gameMap[n] = 1;
    }
    leds[n*2] = CRGB(100,100,100);
    leds[(n*2)+1] = CRGB(100,100,100);;
  }
  FastLED.show();
  state = 1;
  lcd.setCursor(0, 1);
  lcd.print("3... ");
  delay(1000);
  lcd.print("2... ");
  delay(1000);
  lcd.print("1... ");
  delay(1000);
  FastLED.clear();
  FastLED.show();
  return;
}

void guessState(){
  guessed = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zaznacz poprawne pola!");
  lcd.setCursor(0, 1);
  while(state == 1 && lives>0){
    lcd.clear();
    lcd.print(guessed);
    lcd.print("/");
    lcd.print(count);
    char key = keypad.waitForKey();
    if(guessed == count){
      state = 2;
    }
  }
  FastLED.clear();
  FastLED.show();
  if(lives==0)
    state = 0;
}

void winState(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gratulacje!");
  lcd.setCursor(0, 1);
  lcd.print("Kontynuuj...");
  char key = keypad.waitForKey();
  state = 0;
  count++;
}

void clickedButton(int number){
  if(state == 1){
    if(gameMap[number] == 1){
      leds[number*2] = CRGB(0,100,0);
      leds[(number*2)+1] = CRGB(0,100,0);
      guessed++;
    }
    else
    {
      leds[number*2] = CRGB(100,0,0);
      leds[(number*2)+1] = CRGB(100,0,0);
      lives--;
    }
    FastLED.show();
  }
}

void keypadEvent(KeypadEvent key){
  if (keypad.getState() == PRESSED && level == 1){
      switch (key){
        case '1':
          clickedButton(30);
        break;
        case '2': 
          clickedButton(29);
        break;
        case '3': 
          clickedButton(18);
        break;
        case '4': 
          clickedButton(17);
        break;
        case '5': 
          clickedButton(6);
        break;
        case '6': 
          clickedButton(5);
        break;
        case '7': 
          clickedButton(31);
        break;
        case '8': 
          clickedButton(28);
        break;
        case '9':
          clickedButton(19);
        break;
        case '0': 
          clickedButton(16);
        break;
        case 'A': 
          clickedButton(7);
        break;
        case 'B': 
          clickedButton(4);
        break;
        case 'C': 
          clickedButton(32);
        break;
        case 'D': 
          clickedButton(27);
        break;
        case 'E':
          clickedButton(20);
        break;
        case 'F': 
          clickedButton(15);
        break;
        case 'G': 
          clickedButton(8);
        break;
        case 'H': 
          clickedButton(3);
        break;
        case 'I': 
          clickedButton(33);
        break;
        case 'J': 
          clickedButton(26);
        break;
        case 'K': 
          clickedButton(21);
        break;
        case 'L': 
          clickedButton(14);
        break;
        case 'M':
          clickedButton(9);
        break;
        case 'N': 
          clickedButton(2);
        break;
        case 'O': 
          clickedButton(34);
        break;
        case 'P': 
          clickedButton(25);
        break;
        case 'R': 
          clickedButton(22);
        break;
        case 'S': 
          clickedButton(13);
        break;
        case 'T': 
          clickedButton(10);
        break;
        case 'W': 
          clickedButton(1);
        break;
        case '!':
          clickedButton(35);
        break;
        case '@': 
          clickedButton(24);
        break;
        case '#': 
          clickedButton(23);
        break;
        case '$': 
          clickedButton(12);
        break;
        case '%': 
          clickedButton(11);
        break;
        case '^': 
          clickedButton(0);
        break;
      }
  }
}
