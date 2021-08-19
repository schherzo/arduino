const int PIR1 = 9;
const int PIR2 = 10;
const int DOOR = 11;

int visitors = 0;
int lastPIRdetected = 0;
bool PIR1_active = false;
bool PIR2_active = false;

int pin[] = {2,3,4,5,6,7,8};
int d[10][7] = {
  {0,0,0,0,0,0,1}, //0
  {1,0,0,1,1,1,1}, //1
  {0,0,1,0,0,1,0}, //2
  {0,0,0,0,1,1,0}, //3
  {1,0,0,1,1,0,0}, //4
  {0,1,0,0,1,0,0}, //5
  {0,1,0,0,0,0,0}, //6
  {0,0,0,1,1,1,1}, //7
  {0,0,0,0,0,0,0}, //8
  {0,0,0,0,1,0,0}, //9
};

void setup()
{
  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(DOOR, OUTPUT);
  
  for(int i=0;i<8;i++)
      pinMode(pin[i], OUTPUT);
  
  Serial.begin(9600); 
  Serial.println("Visitor counter");
  Serial.println("Welcome");
}

void print(int n)
{
  for(int i=0;i<7;i++)
    digitalWrite(pin[i],d[n][i]);
}

void updateCount(int x)
{
  visitors+=x;
  lastPIRdetected=0; //reset the last PIR detected
}
void loop()
{
  // ----------- check PIR1 ----------------
  if (digitalRead(PIR1) == HIGH) 
  {
    if ( !PIR1_active ) 
    {
      PIR1_active = true;
      if (lastPIRdetected == 0 && !PIR2_active) 
      { 
        if(visitors<9)
        {
          // new start
          lastPIRdetected = 1;
          Serial.println("In PIR1: Visitor Entered");
          updateCount(1);
          Serial.println("Visitors:" + String(visitors));
          analogWrite(DOOR, 100);
          print(visitors);
          delay(5000);
          analogWrite(DOOR, 0);
        }
        else
        {
          Serial.println("MAXIMUM CAPACITY");
          print(visitors);
          delay(5);
        }
      } 
      else if (lastPIRdetected == 2) 
      { // if we were in PIR2 before
        updateCount(-1);  
        Serial.println("Visitor exited");
        Serial.println("Visitors:" + String(visitors));
        analogWrite(DOOR, 100);
        print(visitors);
        delay(5000);
        analogWrite(DOOR, 0);
      }
    }
  }
  else 
    PIR1_active = false ;  // reenable PIR1*/
  
  
  // ----------- check PIR2 ----------------  
  if (digitalRead(PIR2) == HIGH )
  { 
    if ( !PIR2_active ) 
    {
      PIR2_active = true;
      
      if (lastPIRdetected == 0 && !PIR1_active) 
      { // new start
        if (visitors > 0) 
        {
          lastPIRdetected = 2;   

          Serial.println("In PIR2: Visitor exited");
          updateCount(-1);
          Serial.println("Visitors:" + String(visitors));
          analogWrite(DOOR, 100);
          print(visitors);
          delay(5000);
          analogWrite(DOOR, 0);
        } 
        else
        {
          Serial.println("No more visitors to exit");   
          print(visitors);
          delay(5);
        }
      } 
      else if (lastPIRdetected == 1) 
      {  // if we were in PIR1 before
        if(visitors<=9)
        {
          Serial.println("In PIR1: Visitor Entered");
          updateCount(1);
          Serial.println("Visitors:" + String(visitors));
          analogWrite(DOOR, 100);
          print(visitors);
          delay(5000);
          analogWrite(DOOR, 0);
        }
        else
        {
          Serial.println("MAXIMUM CAPACITY");
          print(visitors);
          delay(5);
        }
      }
    }
  } 
  else 
    PIR2_active = false; // reenable PIR2
}

