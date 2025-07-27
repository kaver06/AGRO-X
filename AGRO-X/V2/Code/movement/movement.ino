//left motors
#define out1_a 2
#define out1_b 3
#define out1_e 11

//right motors
#define out2_a 5
#define out2_b 4
#define out2_e 10

int motoSpeed_1=255;
int motoSpeed_2=75;

void setup()
{
  pinMode(out1_a,OUTPUT);
  pinMode(out1_b,OUTPUT);
  pinMode(out1_e,OUTPUT);
  pinMode(out2_a,OUTPUT);
  pinMode(out2_b,OUTPUT);
  pinMode(out2_e,OUTPUT);
}

  void Forward()
  {
    analogWrite(out1_e,motoSpeed_1);
    analogWrite(out2_e,motoSpeed_1);
    digitalWrite(out1_a,HIGH);
    digitalWrite(out2_a,HIGH);
    digitalWrite(out1_b,LOW);
    digitalWrite(out2_b,LOW);
  }

  void Backward()
  {
    analogWrite(out1_e,motoSpeed_1);
    analogWrite(out2_e,motoSpeed_1);
    digitalWrite(out1_a,LOW);
    digitalWrite(out2_a,LOW);
    digitalWrite(out1_b,HIGH);
    digitalWrite(out2_b,HIGH);
  }

void Sharpright()
{
  analogWrite(out1_e,motoSpeed_1);
  analogWrite(out2_e,motoSpeed_1);
  digitalWrite(out1_a,HIGH);
  digitalWrite(out2_a,LOW);
  digitalWrite(out1_b,LOW);
  digitalWrite(out2_b,HIGH);
}

void Sharpleft()
{
  analogWrite(out1_e,motoSpeed_1);
  analogWrite(out2_e,motoSpeed_1);
  digitalWrite(out1_a,LOW);
  digitalWrite(out2_a,HIGH);
  digitalWrite(out1_b,HIGH);
  digitalWrite(out2_b,LOW);
}

void Left()
{
  analogWrite(out1_e,motoSpeed_2);
  analogWrite(out2_e,motoSpeed_1);
  digitalWrite(out1_a,HIGH);
  digitalWrite(out2_a,HIGH);
  digitalWrite(out1_b,LOW);
  digitalWrite(out2_b,LOW);
}

void Right()
{
  analogWrite(out1_e,motoSpeed_1);
  analogWrite(out2_e,motoSpeed_2);
  digitalWrite(out1_a,HIGH);
  digitalWrite(out2_a,HIGH);
  digitalWrite(out1_b,LOW);
  digitalWrite(out2_b,LOW);
}

void Stop()
{
  digitalWrite(out1_a,LOW);
  digitalWrite(out2_a,LOW);
  digitalWrite(out1_b,LOW);
  digitalWrite(out2_b,LOW);
}

void loop()
{
  Sharpright();
  
}
