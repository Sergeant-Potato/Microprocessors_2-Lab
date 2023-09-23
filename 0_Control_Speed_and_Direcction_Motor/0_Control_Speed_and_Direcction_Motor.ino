/*
  PWM And Speed Direcction.
  Control a DC motor using Pulce Wide Modulation
  Show the percet of High snd low in the Monitor
  and the high in the PORTB
 
          By Roman Lopez Ph. D.
          October 30, 2012
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

    int Time1,Time2,i,j,k;
    int Dir=0,Speed;
    int Hpulse,Lpulse;
    char CW=0b00000001;
    char CCW=0b00000010;
    char Mstop=0b00000000;
    int PulceWide=50;
   // This is the Code for the seven segment display.
    char SevenSeg[16]={0x3F,0b00000110,0x5b,0x4f,0x66,0x6d,0x7c,0x67,0x7f,0x67,0x77,0x39};
  
// the setup routine runs once when you press reset:
void setup() {                
  
      DDRL = 0b11111111;
      DDRB=0b11111111;
      Dir=0;
   // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
   
}

// the loop routine runs over and over again forever:
void loop() {
    for(i=0;i<PulceWide;i+=5){
        Time1=i;
        Time2=PulceWide-i;
        Hpulse=((Time1*100)/PulceWide);
        Lpulse=((Time2*100)/PulceWide);
        k=((i*10)/PulceWide);
        PORTB=~SevenSeg[k];
        Serial.print("(PWM) Hight =  ");
        Serial.print(Hpulse);
        Serial.print("%, Low =");
        Serial.print(Lpulse);
        Serial.print("%  PORTB = ");
        Serial.println(k,DEC);
        
         if(Dir){  //Clockwise direction
           for(j=0;j<100;j++){
            PORTL=CW;
            delay(Time1);
             PORTL=Mstop;
             delay(Time2);
            }
           }
          else{ //Counter Clockwise direction
            for (int j=0;j<100;j++){
               PORTL=CCW;
               delay(Time1);
               PORTL=Mstop;
               delay(Time2); 
              }
            }
        }
      if(Dir==0)
        {Dir=1;}
        else {Dir=0;}  
      
 }
     
