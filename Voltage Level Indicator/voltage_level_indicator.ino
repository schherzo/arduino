int pin[]={2,3,4,5,6};

void setup()
{
  Serial.begin(9600);
  for(int i=0;i<5;i++)
  {
    pinMode (pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
  }  
}

void loop()
{
  //input = map(analogRead(A0), 0, 1023, 0, 300);
  int input=analogRead(A0);
  float voltage = input * (5.0 / 1023.0);
  if(1>=voltage)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if(2>=voltage)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if(3>=voltage)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if(4>=voltage)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }
  else if(5>=voltage)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }
}
