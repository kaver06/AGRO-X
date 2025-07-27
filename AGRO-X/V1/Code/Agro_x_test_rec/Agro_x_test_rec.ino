//Updated test code

#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

#define LDR 4
#define BUZ 5
#define LED 7

#define HRX 13
#define HTX 2

#define INT1 8
#define INT2 9
#define INT3 10
#define INT4 11
#define CONTROL_PIN 12
#define VOLTAGE_CONTROL_PIN 6

volatile bool TOGGLESTATE=true;
String received;
int state;


float Ambient = 0;
float Object = 0;
float threshold = 3;
int  StepNum= 0;
int StepDelay = 5;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial hc12(HRX, HTX);

void setup()
{
  Serial.begin(9600);
  hc12.begin(9600);

  while(!Serial);
  Serial.println("System check");

  if(!mlx.begin())
  {
    Serial.println("Connection error...!");
    while(1);
  };

  pinMode(LDR, INPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);
  pinMode(CONTROL_PIN,OUTPUT);
  pinMode(VOLTAGE_CONTROL_PIN,INPUT);

  //attachInterrupt(digitalPinToInterrupt(2),WIRE, CHANGE);
  digitalWrite(CONTROL_PIN,HIGH);
  digitalWrite(LED,HIGH);

  
  hc12.write("Connecting");

}

void WIRE()
{
   if (hc12.available() > 0)
  {
    received = hc12.readString(); 
  
    if (received == "STOP") 
    {
      TOGGLESTATE=!TOGGLESTATE;
      digitalWrite(CONTROL_PIN,TOGGLESTATE);
    }
  }
}

void loop()
{
  WIRE();
  state=digitalRead(VOLTAGE_CONTROL_PIN);
  Serial.println(state);
  int LDRValue = digitalRead(LDR);
 if(state==HIGH)
  {
    if(LDRValue== 1)
    {
      rotateStepper180();
      delay(2000);
      rotateStepper360();
    }
  }

}



int MLXTemperature()
{
  Ambient = mlx.readAmbientTempC();
  Object = mlx.readObjectTempC();
    Serial.println(Object);


  if(Object-Ambient> threshold)
  {
    
    //Serial.println("intrution");
    hc12.write("det");
    for(int i=0;i<5;i++)
    {
      digitalWrite(LED, LOW);
      digitalWrite(BUZ, HIGH);
      delay(300);
      digitalWrite(LED, HIGH);
      digitalWrite(BUZ, LOW);
      delay(100);
      }  
    
  }
}

void rotateStepper180()
{
  
  for(int i=0;i<1024;i++)
  {
    OneStep(false);
    delay(StepDelay);
    MLXTemperature();
  }

    for(int i=0;i<1024;i++)
  {
    OneStep(true);
    delay(StepDelay);
    MLXTemperature();
  }
}

void rotateStepper360()
{
  
  for(int i=0;i<2048;i++)
  {
    OneStep(false);
    delay(StepDelay);
    MLXTemperature();
  }

    for(int i=0;i<2048;i++)
  {
    OneStep(true);
    delay(StepDelay);
    MLXTemperature();
  }
}

void OneStep(bool dir)
{
  if(dir)
  {
    switch(StepNum)
    {
      case 0:
        digitalWrite(INT1, HIGH);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, LOW);
      break;
      
      case 1:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, HIGH);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, LOW);
      break;

      case 2:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, HIGH);
        digitalWrite(INT4, LOW);
      break;

      case 3:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, HIGH);
      break;
    } 
  }
  
  else 
  {
    switch(StepNum)
    {
      case 0:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, HIGH);
      break;

      case 1:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, HIGH);
        digitalWrite(INT4, LOW);
      break;

      case 2:
        digitalWrite(INT1, LOW);
        digitalWrite(INT2, HIGH);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, LOW);
      break;

      case 3:
        digitalWrite(INT1, HIGH);
        digitalWrite(INT2, LOW);
        digitalWrite(INT3, LOW);
        digitalWrite(INT4, LOW);
    } 
  }
  StepNum++;

  if(StepNum > 3)
  {
    StepNum = 0;
  }
}