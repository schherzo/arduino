int m=3;
int s1=7;
int s2=6;
int s3=5;
int s4=4;
void setup()
{
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);

  pinMode(m, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(s1)==HIGH)
  {
    analogWrite(m,0);
    Serial.println("0% duty cycle");
  }
  else if(digitalRead(s2)==HIGH)
  {
    analogWrite(m,63);
    Serial.println("25% duty cycle");
  }
  else if(digitalRead(s3)==HIGH)
  {
    analogWrite(m,127);
    Serial.println("50% duty cycle");
  }
  else if(digitalRead(s4)==HIGH)
  {
    analogWrite(m,191);
    Serial.println("75% duty cycle");
  }
  else 
  {
    analogWrite(m,255);
    Serial.println("100% duty cycle");
  }
}
