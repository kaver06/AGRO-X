//Updated Transmitter Code

#include <SoftwareSerial.h>

#define BUZ 7
#define HRX 2
#define HTX 3

#define LED 5
#define PUSH_PIN 6

volatile unsigned long START_TIME=millis();
unsigned long DELAY_PRESET = 60;
volatile bool TOGGLESTATE=false;

SoftwareSerial hc12(HRX,HTX);

void setup() 
{
  Serial.begin(9600);
  hc12.begin(9600);

  pinMode(BUZ, OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(PUSH_PIN,INPUT);
}

void loop() 
{
  
  if (hc12.available() > 0)
  {
    String receivedData = hc12.readString(); 
    
    if (receivedData == "Connecting") 
    {
      Serial.println("Connected sucessfully");
        digitalWrite(BUZ, HIGH);
        digitalWrite(LED,HIGH);
        delay(1500);
        digitalWrite(BUZ, LOW);
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(BUZ, HIGH);
        digitalWrite(LED,HIGH);
        delay(500);
        digitalWrite(BUZ, LOW);
        digitalWrite(LED, LOW);

    }

  }
  
 if (hc12.available() > 0)
  {
    String received = hc12.readString(); 
  
    if (received == "det") 
    {
      Serial.println("INTRUSION DETECTED...!");
      digitalWrite(BUZ, HIGH);
      digitalWrite(LED,HIGH);
      delay(4000);
      digitalWrite(BUZ, LOW);
      digitalWrite(LED, LOW); 
      delay(50);
      digitalWrite(BUZ, HIGH);
      digitalWrite(LED,HIGH);
      delay(100);
      digitalWrite(BUZ, LOW);
      digitalWrite(LED, LOW);

    }
 }
  volatile unsigned long END_TIME=millis();
  if(END_TIME-START_TIME>DELAY_PRESET)
  {
    if(digitalRead(PUSH_PIN)==HIGH)
    {
      hc12.write("STOP");
      TOGGLESTATE!=TOGGLESTATE;
      START_TIME=END_TIME;
      digitalWrite(BUZ, HIGH);
      digitalWrite(LED,HIGH);
      delay(500);
      digitalWrite(BUZ, LOW);
      digitalWrite(LED, LOW);
      
    }
  }
}