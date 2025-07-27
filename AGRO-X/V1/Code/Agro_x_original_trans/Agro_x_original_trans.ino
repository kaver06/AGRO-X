//Previous Original code

#include <SoftwareSerial.h>

#define BUZ 7
#define HRX 2
#define HTX 3
#define LED 6

SoftwareSerial hc12(HRX,HTX); 

void setup() 
{
  Serial.begin(9600);
  hc12.begin(9600);

  pinMode(BUZ,OUTPUT);
  pinMode(LED,OUTPUT);
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
        digitalWrite(LED, HIGH);
        delay(1000);
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
        digitalWrite(LED, HIGH);
        delay(2000);
        digitalWrite(BUZ, LOW);
        digitalWrite(LED, LOW);

    }
 }
}