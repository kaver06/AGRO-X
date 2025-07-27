//Updated receiver code

#include <Adafruit_MLX90614.h>

#define RF 2
#define BUZ 8
#define LED 3

#define INT1 7
#define INT2 6
#define INT3 5
#define INT4 4

#define VOLTAGE_CONTROL_PIN 11
#define esp_send_pin 10

int state;


float Ambient = 0;
float Object = 0;
float threshold = 3;
int  StepNum= 0;
int StepDelay = 5;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("System check");

  if(!mlx.begin())
  {
    Serial.println("Connection error...!");
    while(1);
  };

  pinMode(RF, INPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);
  pinMode(VOLTAGE_CONTROL_PIN,INPUT);
  pinMode(esp_send_pin,OUTPUT);

  digitalWrite(esp_send_pin,LOW);
  digitalWrite(LED,LOW);
  digitalWrite(BUZ,LOW);
}

void loop()
{
  state=digitalRead(VOLTAGE_CONTROL_PIN);
  Serial.println(state);

 if(state==HIGH)
  {
    int RF_value = digitalRead(RF);
    if(RF_value== 1)
    {
      rotateStepper180();
      delay(2000);
      rotateStepper180();
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
    
    Serial.println("intrution");
    digitalWrite(esp_send_pin,HIGH);
    Serial.println();
    digitalWrite(BUZ,HIGH);
    for(int i=0;i<10;i++)
    {
      digitalWrite(LED, HIGH);
      delay(300);
      digitalWrite(LED, LOW);
      delay(100);
    }  
    digitalWrite(BUZ, LOW);
    digitalWrite(esp_send_pin,LOW);
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