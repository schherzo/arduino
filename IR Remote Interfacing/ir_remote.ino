#include<IRremote.h>

int rev_pin=11;
IRrecv ir(rev_pin);
decode_results result; //inbuilt structure 

void setup()
{
  Serial.begin(9600);
  ir.enableIRIn();
}

void loop()
{
  if(ir.decode(&result))
  {
    Serial.println(result.value);
    ir.resume();
  }
  delay(100);
}
