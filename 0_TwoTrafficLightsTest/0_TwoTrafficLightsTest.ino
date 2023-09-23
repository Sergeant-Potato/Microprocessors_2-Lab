/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
/* Roman Lopez Ph. D. */
/****************************************************/
//Traffic Light 1
#define cross 28
#define red 22
#define yellow 24
#define green 26
//Traffic Light 2
#define cross2 29
#define red2 23
#define yellow2 25
#define green2 27
#define button 2
#define button_2 3
#define Delay_time 500
#define Green_time 5
#define Yellow_time 3
#define Red_time 5
volatile int button_state = 0;
int i = 0;
int Flag;
int Flag2;
int Ligth_State;
void setup() {
pinMode(cross, OUTPUT);
pinMode(red,OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
pinMode(cross2, OUTPUT);
pinMode(red2,OUTPUT);
pinMode(yellow2, OUTPUT);
pinMode(green2, OUTPUT);
pinMode(button, INPUT);
pinMode(button_2, INPUT);
attachInterrupt(0,SetFlag,CHANGE); //Attached the Interrup subroutine
attachInterrupt(1,SetFlag2,CHANGE); //Attached the Interrup subroutine
Serial.begin(9600);
Flag=0;
Flag2=0;
}
void loop() {
LOOP:
//Set the state flag, 1=gree,2=yellow and 3=red
//Set Green ON, ref and Yellow OFF
// Green State for first traffic light
digitalWrite(red,LOW);
digitalWrite(yellow,LOW);
digitalWrite(green,HIGH);
digitalWrite(cross,LOW);
// red State for second traffic light
digitalWrite(red2,HIGH);
digitalWrite(yellow2,LOW);
digitalWrite(green2,LOW);
digitalWrite(cross2,LOW);
for (i=0;i<=Green_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1)
{
Ligth_State=1;
Pedestian();
goto LOOP;
}
}
//Yellow State just for the first traffic light
digitalWrite(green,LOW);
digitalWrite(yellow,HIGH);
for (i=0;i<=Yellow_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1)
{
Ligth_State=2;
Pedestian();
goto LOOP;
}
}
// Red State just for the first traffic light
digitalWrite(yellow,LOW);
digitalWrite(red,HIGH);
for (i=0;i<=Red_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1)
{
Ligth_State=3;
Pedestian();
goto LOOP;
}
}
// Green State for second traffic light
digitalWrite(red2,LOW);
digitalWrite(green2,HIGH);
//digitalWrite();
for (i=0;i<=Green_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1)
{
Ligth_State=4;
Pedestian();
goto LOOP;
}
}
//Yellow State for the second traffic light
digitalWrite(green2,LOW);
digitalWrite(yellow2,HIGH);
for (i=0;i<=Red_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1) {
Ligth_State=5;
Pedestian();
goto LOOP;
}
}
//Red State for the second traffic light
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
for (i=0;i<=Red_time;i++)
{delay(Delay_time);
if(Flag==1 || Flag2==1) {
Ligth_State=6;
Pedestian();
goto LOOP;
}
}
}
void SetFlag(void)
{
Flag=1;
}
void SetFlag2(void)
{
Flag2=1;
}
void Pedestian(void){
switch (Ligth_State) {
  case 1:{// Off green on Yellow
    // if flag 2 is 1 cross 2 will turn on
    if(Flag2==1){
    digitalWrite(cross2,HIGH);
    delay(5000);
    break;
    }
    else if(Flag==1){
    digitalWrite(green,LOW); //off Green set Yellow
    digitalWrite(yellow,HIGH);
    delay(2000);
    // Set Red on in first traffic light and Pedestrian on
    digitalWrite(yellow,LOW); //off Green set Yellow
    digitalWrite(red,HIGH);
    digitalWrite(red2,LOW);
    digitalWrite(green2,HIGH);
    digitalWrite(cross,HIGH);
    delay(5000);
    break;
    }
}
   case 2:{//YELLOW state
  if(Flag2==1){
  delay(500); //Keep yellow for 1/2 second
  delay(1000);
  digitalWrite(yellow,LOW); //off Green set Yellow
  digitalWrite(red,HIGH);
  digitalWrite(red2,LOW);
  digitalWrite(green2,HIGH);
  digitalWrite(cross2,HIGH);
  delay(2000);
  digitalWrite(green2,LOW);
  digitalWrite(yellow2,HIGH);
  delay(2000);
  digitalWrite(yellow2,LOW);
  digitalWrite(red2,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
    break;
} else if(Flag==1)//if flag one will keep yellow for 1/2 second
{
delay(500);
delay(1000);
// Set Red on and Pedestrian on
digitalWrite(yellow,LOW); //off Green set Yellow
digitalWrite(red,HIGH);
digitalWrite(cross,HIGH);
digitalWrite(red2,LOW);
digitalWrite(green2,HIGH);
delay(5000);
break;
}
}
case 3:{//Pedestrian on, red on
if(Flag2==1)
{
digitalWrite(cross2,HIGH);
digitalWrite(red2,LOW);
digitalWrite(green2,HIGH);
delay(2000);
digitalWrite(green2,LOW); //off Green set Yellow for second traffic light
digitalWrite(yellow2,HIGH);
delay(2000);
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,HIGH);
delay(2000);
break;
}
else if(Flag==1){
digitalWrite(cross,HIGH);
delay(2000);
digitalWrite(red2,LOW);
digitalWrite(green2,HIGH);
digitalWrite(cross,HIGH);
delay(2000);
break;
}
}
case 4:{//GREEN state second traffic light
if(Flag2==1){
delay(2000);
digitalWrite(green2,LOW);
digitalWrite(yellow2,HIGH);
delay(2000);
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,HIGH);
digitalWrite(cross2,HIGH);
delay(2000);
break;
}
else if(Flag==1){
//digitalWrite(red,LOW);
//digitalWrite(green,HIGH);
digitalWrite(cross,HIGH);
delay(2000);
break;
}
}
case 5:{//YELLOW State for second traffic light
if(Flag2==1){
digitalWrite(cross2,HIGH);
delay(2000);
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,HIGH);
delay(2000);
break;
}
else if(Flag==1){
//delay(20
digitalWrite(cross,HIGH);
delay(1000);
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,HIGH);
delay(2000);
digitalWrite(green,LOW);
digitalWrite(yellow,HIGH);
delay(2000);
digitalWrite(yellow,LOW);
digitalWrite(red,HIGH);
digitalWrite(red2,LOW);
digitalWrite(green2,HIGH);
delay(1000);
break;
}
}
case 6: {//RED state second traffic light
    if(Flag2==1){
    digitalWrite(cross2,HIGH);
    delay(1000);
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    delay(1000);
    break;
    }
  else if(Flag==1){
    digitalWrite(cross,HIGH);
    delay(1000);
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    delay(2000);
    digitalWrite(green,LOW);
    digitalWrite(yellow,HIGH);
    delay(2000);
    digitalWrite(yellow,LOW);
    digitalWrite(red,HIGH);
    digitalWrite(red2,LOW);
    digitalWrite(green2,HIGH);
    delay(1000);
    break;
    }
}
default:{};
}
  if(Flag == 1){
  for (i=0;i<=5;i++)
  {digitalWrite(cross,LOW);
  delay(1000);
  digitalWrite(cross,HIGH);
  delay(1000);
  }
}
else if(Flag2 == 1){
  for (i=0;i<=5;i++)
  {
  digitalWrite(cross2,LOW);
  delay(1000);
  digitalWrite(cross2,HIGH);
  delay(1000);
  }
}
if (Flag==1){
delay(1000);
digitalWrite(cross,LOW);
digitalWrite(green2,LOW);
digitalWrite(yellow2,HIGH);
delay(2000);
digitalWrite(yellow2,LOW);
digitalWrite(red2,HIGH);
delay(2000);
//break;
}
Flag=0;
Flag2=0;
}
