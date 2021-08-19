#include<Keypad.h>
#include<LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[ROWS]={A0,A1,A2,A3};
byte colPins[COLS]={8,9,10,11};
int LCDRow=0;


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins, ROWS, COLS);
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(LCDRow,0);
}

void loop()
{
  char key = keypad.getKey();
  if(key)
  {
    lcd.print(key);
    lcd.setCursor(++LCDRow,0);
  }
}
