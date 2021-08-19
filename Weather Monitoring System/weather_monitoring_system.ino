#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int lightlevel=0;
int LDR = A0; //light detection
int TMP = A1; //temperature detection
int sensorPin = A1;

unsigned long previousMil = 0;
unsigned long currentMil =0;
const long period = 3000;

int hour=8;
int min=0;
int sec=0;

void setup() {
  Serial.begin(9600);
  lcd.begin (16, 2);
}

void loop() {
  int reading = analogRead(sensorPin);
  
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
 
  // print out the voltage
  //Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  
  //converting from 10 mv per degree wit 500 mV offset to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");
 
  // now convert to Fahrenheit
  //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  //Serial.print(temperatureF); Serial.println(" degrees F");
 
  //LDR 
  lightlevel = analogRead(LDR);  
  Serial.println(lightlevel); 
  
  //CO2 Level Detection
  float co2 = analogRead(A0);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  print_time();
  delay(3000); //delay of 3 seconds
  /*lcd.setCursor(0, 0);
  lcd.print(temperatureC); lcd.print(" degrees C"); 
  lcd.setCursor(0, 1);*/
  //lcd.print("light level: ");lcd.print(lightlevel);
  //lcd.setCursor(0,2);
  for (int position = 0; position < 16; position++) {
  	lcd.setCursor(0, 0);
    lcd.print(temperatureC); lcd.print(" degrees C"); 
    lcd.setCursor(0, 1);
    lcd.print("light level: ");lcd.print(lightlevel);
    lcd.print(" co2 level: ");lcd.print(co2);
    lcd.scrollDisplayLeft();
    delay(500);
  }
  delay(3000);
}

void print_time(){
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
  delay(1000); 
  sec+=1;
    int hourtemp=0;
    if(hour>12) {hourtemp=(hour-12);}
    else if(hour==0){hourtemp=12;} //12.00 AM
  else {hourtemp=hour;}
  
    if(hourtemp<10){
      lcd.setCursor(0,1); lcd.print(0);
      lcd.setCursor(1,1); lcd.print(hourtemp);
    }
    else {
      lcd.setCursor(0,1); lcd.print(hourtemp);
    }
    lcd.setCursor(2,1); lcd.print(":");
  
    if(min<10){
      lcd.setCursor(3,1); lcd.print(0);
      lcd.setCursor(4,1); lcd.print(min);
    }
    else {
      lcd.setCursor(3,1); lcd.print(min);
    }
    lcd.setCursor(5,1); lcd.print(":");
  
    if(sec<10){
      lcd.setCursor(6,1); lcd.print(0);
      lcd.setCursor(7,1); lcd.print(sec);
    }
    else {
      lcd.setCursor(6,1); lcd.print(sec);
    }
   
    if(hour<12){
   	  lcd.setCursor(9,1); lcd.print("AM");

  	}
    else{
      lcd.setCursor(9,1); lcd.print("PM");
  	}
    lcd.setCursor(11,1); lcd.print(" ");
}
