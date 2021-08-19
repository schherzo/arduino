/*Included Libraries*/
#include<Keypad.h>

/*Definitions*/
#define CLK 10
#define SS 11
#define MOSI 12
#define MISO 13
#define FALSE 0 
#define TRUE 1

/*Function prototype*/
void setBits(char keypressed);

/*Variables*/
unsigned long prevTick = 0.0;
unsigned long lastTime = 0.0;
int clockState = LOW;
int prevClkState = LOW;
unsigned int clkCounter = 0;
unsigned int pressTime;
char keypressed;
int bitNum[4];
int bitSent[] = {FALSE, FALSE, FALSE, FALSE};
int bitsToSend = 0;
int ii;

/*Constants*/
const byte numRows = 4; //number of keypad rows
const byte numCols = 4; //number of keypad cols

char keymap[numRows][numCols] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[numRows] = {9,8,7,6}; //rows 0 to 3
byte colPins[numCols] = {5,4,3,2}; //columns 0 to 3

//Set up for the sorting key pressed 
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
  //Set pins as inputs or outputs
  pinMode(CLK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SS, OUTPUT);
  
  //Set initial output pin states
  digitalWrite(CLK, LOW);
  digitalWrite(MOSI, LOW);
  digitalWrite(SS, HIGH);
}//end setup

void loop()
{
  //Clock code 
  if((millis()-prevTick)>=1000) //1000 milliseconds has passed
  {
    clockState =!clockState; //toggle clockState
    digitalWrite(CLK, clockState);
    prevTick = millis(); //restart timing from this point 
    clkCounter++;
  }
  
  //Sending any key press
  if(bitsToSend > 0)
  {
    if(!(bitSent[bitsToSend - 1])) //if next bit not yet sent
    {
      if((clkCounter - pressTime)>(-1 * bitsToSend + 5))
      {
        if((clockState==LOW)&&((millis() - lastTime)>1000))
        {
          digitalWrite(SS,LOW);
          digitalWrite(MOSI, bitNum[bitsToSend - 1]);
          bitSent[bitsToSend - 1] = TRUE;
          bitsToSend--;
          lastTime = millis();
        }
      }
    }   
  }
  else //no more bits to send
  {
    if(digitalRead(MISO)==HIGH)
    {
      if((millis()-lastTime)>2000)
      {
        digitalWrite(SS, HIGH);
        digitalWrite(MOSI,LOW);
      }
    }
    
    /*Key Response*/
    keypressed=myKeypad.getKey();
    if(keypressed!=NO_KEY)
    {
      setBits(keypressed);
      pressTime = clkCounter;
      lastTime = millis();
      
      bitsToSend = 4;
      for(ii=0; ii<4; ii++)
      {
        bitSent[ii]=FALSE;
      }
    }
  }
  delay(10); //delay a little bit to improve
}

void setBits(char keypressed)
{
  switch(keypressed)
  {
    case '0':
    	bitNum[3]=0;
    	bitNum[2]=0;
    	bitNum[1]=0;
    	bitNum[0]=0;
    	break;
    case '1':
    	bitNum[3]=0;
    	bitNum[2]=0;
    	bitNum[1]=0;
    	bitNum[0]=1;
    	break;
    case '2':
    	bitNum[3]=0;
    	bitNum[2]=0;
    	bitNum[1]=1;
    	bitNum[0]=0;
    	break;
    case '3':
    	bitNum[3]=0;
    	bitNum[2]=0;
    	bitNum[1]=1;
    	bitNum[0]=1;
    	break;
    case '4':
    	bitNum[3]=0;
    	bitNum[2]=1;
    	bitNum[1]=0;
    	bitNum[0]=0;
    	break;
    case '5':
    	bitNum[3]=0;
    	bitNum[2]=1;
    	bitNum[1]=0;
    	bitNum[0]=1;
    	break;
    case '6':
    	bitNum[3]=0;
    	bitNum[2]=1;
    	bitNum[1]=1;
    	bitNum[0]=0;
    	break;
    case '7':
    	bitNum[3]=0;
    	bitNum[2]=1;
    	bitNum[1]=1;
    	bitNum[0]=1;
    	break;
    case '8':
    	bitNum[3]=1;
    	bitNum[2]=0;
    	bitNum[1]=0;
    	bitNum[0]=0;
    	break;
    case '9':
    	bitNum[3]=1;
    	bitNum[2]=0;
    	bitNum[1]=0;
    	bitNum[0]=1;
    	break;
    case 'A':
    	bitNum[3]=1;
    	bitNum[2]=0;
    	bitNum[1]=1;
    	bitNum[0]=0;
    	break;
    case 'B':
    	bitNum[3]=1;
    	bitNum[2]=0;
    	bitNum[1]=1;
    	bitNum[0]=1;
    	break;
    case 'C':
    	bitNum[3]=1;
    	bitNum[2]=1;
    	bitNum[1]=0;
    	bitNum[0]=0;
    	break;
    case 'D':
    	bitNum[3]=1;
    	bitNum[2]=1;
    	bitNum[1]=0;
    	bitNum[0]=1;
    	break;
    case '*':
    	bitNum[3]=1;
    	bitNum[2]=1;
    	bitNum[1]=1;
    	bitNum[0]=0;
    	break;
    case '#':
    	bitNum[3]=1;
    	bitNum[2]=1;
    	bitNum[1]=1;
    	bitNum[0]=1;
    	break;
    default:
    	//do nothing if there is no input
    	break;
  }
} //end setbits functiom
