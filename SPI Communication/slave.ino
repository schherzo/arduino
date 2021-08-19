/*Included libraries*/
#include<LiquidCrystal.h>

/*Arduino pin definition*/
#define CLK 7
#define SS 8 
#define MOSI 9
#define MISO 10

/*Variables*/
int clkState = LOW;
int prevClkState = LOW;
byte data = 0x00; //for storing received data
int bitPos = 3; //current bit position
unsigned long timerStart;
LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  //set pins as inputs or outputs
  pinMode(CLK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  
  //set initial states of output pins
  digitalWrite(MISO, LOW);
  
  //set up the LCD's number of columns and rows 
  lcd.begin(16,2);
  lcd.setCursor(0,1);
}

void loop()
{
  clkState = digitalRead(CLK); //align clock 
  if(clkState != prevClkState)
  {
    prevClkState = clkState;
    if(digitalRead(SS)==LOW)
    {
      if(clkState==HIGH)
      {
        if(digitalRead(MOSI)==LOW)
        {
          data &=~(0x01 <<bitPos);
          bitPos--;
        }
        else
        {
          data |= (0x01 <<bitPos);
          bitPos--;
        }
        if(bitPos<0)
        {
          delay(500);
          digitalWrite(MISO,HIGH);
          delay(1000);
          digitalWrite(MISO,LOW);
          bitPos=3;
          lcd.clear();
          lcd.print(data);
        }
      }
    }
  }
  delay(10);
}
