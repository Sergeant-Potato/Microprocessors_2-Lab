/* Do a Rotation (4095 steps) Clock Wise 
 them stop for 3 seconds
              Roman Lopez Ph. D. 10/24/2014
   BYJ48 Stepper motor code
   Connect :
   IN1 >> Pin 3
   IN2 >> Pin 4
   IN3 >> Pin 5
   IN4 >> Pin 6
   VCC ... 5V Prefer to use external 5V Source
   Gnd
       10/24/2013
  */

const int IN1 = 22;
const int IN2 = 23;
const int IN3 = 24;
const int IN4 = 25;
int Steps = 0;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;
void setup()
{
Serial.begin(9600);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT); 
// delay(1000);
Serial.begin(9600);
}
void loop()
{
  while(steps_left>0)
      {
      currentMillis = micros();
      
      if(currentMillis-last_time>=1000)
        {
        stepper(Steps); 
        time=time+micros()-last_time;
        last_time=micros();
        steps_left--;
        }
  }
 
  delay(3000);
  steps_left=4095;
}
//HALF Stepping switching Mode
void stepper(int xw)
  {
   switch(xw)
    {
     case 0:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     case 1:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, HIGH);
     break; 
     case 2:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 3:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 4:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 5:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
       case 6:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 7:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     default:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
    }
    Steps--;
      if(Steps<0)
        Steps=7;
}
