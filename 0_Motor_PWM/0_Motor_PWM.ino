//Use the PORTL pin 0
int Time1=100;
int Time2=4000;
void setup() {
  // put your setup code here, to run once:
DDRL=0b0000001;

}

void loop() {
  // put your main code here, to run repeatedly: 
  PORTL=0;
  delay(Time1);
  PORTL=1;
  delay(Time2);
  PORTL=0;
  delay(Time1);
  PORTL=2;
  delay(Time2);
}
