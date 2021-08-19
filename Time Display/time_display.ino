#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned long previousMil = 0;
unsigned long currentMil =0;
const long period = 3000;

int hour=8;
int min=0;
int sec=0;

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}
void loop()
{ 
  if(sec==60){
    min+=1;
    sec=0;
    if(min==60){
      hour+=1;
      min=0;
      if(hour==24){
        hour=0;
      }
    }
  }
  currentMil = millis();
  //Checking if the 3-second period has occurred
  if (currentMil - previousMil >= period) {
    previousMil = currentMil;
    lcd.clear();
  }
  
  print_time();
  delay(1000); 
  sec+=1;
}
void print_time(){
  
    int hourtemp=0;
    if(hour>12) {hourtemp=(hour-12);}
    else if(hour==0){hourtemp=12;} //12.00 AM
  else {hourtemp=hour;}
  
    if(hourtemp<10){
      lcd.setCursor(0,0); lcd.print(0);
      lcd.setCursor(1,0); lcd.print(hourtemp);
    }
    else {
      lcd.setCursor(0,0); lcd.print(hourtemp);
    }
    lcd.setCursor(2,0); lcd.print(":");
  
    if(min<10){
      lcd.setCursor(3,0); lcd.print(0);
      lcd.setCursor(4,0); lcd.print(min);
    }
    else {
      lcd.setCursor(3,0); lcd.print(min);
    }
    lcd.setCursor(5,0); lcd.print(":");
  
    if(sec<10){
      lcd.setCursor(6,0); lcd.print(0);
      lcd.setCursor(7,0); lcd.print(sec);
    }
    else {
      lcd.setCursor(6,0); lcd.print(sec);
    }
   
    if(hour<12){
   	  lcd.setCursor(9,0); lcd.print("AM");

  	}
    else{
      lcd.setCursor(9,0); lcd.print("PM");
  	}
    lcd.setCursor(11,0); lcd.print(" ");
}
/*void showInfoENG(){
  
    lcd.setCursor(0,0); lcd.print("HH:MM:SS");	
    lcd.setCursor(9,0); lcd.print("12H");
  	lcd.setCursor(13,0); lcd.print("LNG");
  
    lcd.setCursor(0,1); lcd.print("DD.MM.YYYY");
    lcd.setCursor(13,1); lcd.print("DOW");
}*/
