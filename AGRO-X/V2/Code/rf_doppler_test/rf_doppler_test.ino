#define sensor_pin 2

#define led 5
int state;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensor_pin,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  state=digitalRead(sensor_pin);
  if(state==HIGH)
  {
    Serial.println("detected");
    digitalWrite(led,HIGH);
  }
  
  else
  Serial.println("not detected");

}
