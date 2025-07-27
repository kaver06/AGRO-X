#include <HardwareSerial.h>

#define HC12_RX_PIN 16   // Define RX pin for HC-12 module
#define HC12_TX_PIN 17   // Define TX pin for HC-12 module

#define BAUD_RATE_HC12 9600

HardwareSerial HC12Serial(1);

#define CONTROL_PIN 13
#define arduino_recieve_pin 14

String received;
volatile bool TOGGLESTATE=true;
volatile unsigned long start_time=millis();
unsigned long delay_preset=4000;
void setup() 
{
  Serial.begin(9600);
  HC12Serial.begin(BAUD_RATE_HC12, SERIAL_8N1, HC12_RX_PIN, HC12_TX_PIN);
  HC12Serial.write("Connecting");
  pinMode(CONTROL_PIN,OUTPUT);
  pinMode(arduino_recieve_pin,INPUT);
  digitalWrite(CONTROL_PIN,LOW);
}

void WIRE_Less()
{
   if (HC12Serial.available() > 0)
  {
    received = HC12Serial.readString(); 
  
    if (received == "STOP") 
    {
      TOGGLESTATE=!TOGGLESTATE;
      digitalWrite(CONTROL_PIN,TOGGLESTATE);
      Serial.println(TOGGLESTATE);
      Serial.println("yess");
    }
  }
}
void WIRE()
{

  int recieve_pin_state=digitalRead(arduino_recieve_pin);
  volatile unsigned long end_time=millis();
  if(recieve_pin_state==1)
  {
    if(end_time-start_time>delay_preset)
    {
      start_time=end_time;
      HC12Serial.write("det");
      Serial.println("yea");
    }
    
  }
}

void loop() 
{
  WIRE_Less();
  WIRE();
}




