
#define pinA A13

const int nIterations = 1136;
const int nTests = 10;



//const double L = 500;
//const double k = 0.00000005670;
//const double R = 10000;

void setup() {
  Serial.begin(9600);
  Serial.println("PHOTORESISTOR - DISTANCE PROGRAM");
  Serial.println("This program will try to approximate the distance a light source with a photoresistor.\n");
  Serial.println("USAGE: In order to properly use this program the user must first decide on the units of measurements "); 
  Serial.println("for the distance of the light source and enable the TEST MODE of itself. After these two steps have ");
  Serial.println("been accomplished, the user will then aid the program on acquiring certain measurements of which he ");
  Serial.println("or she must then use to create a spline-related equation. Lastly, the user will input this equation ");
  Serial.println("in the code, reset the Arduino, disable the TEST MODE state of the program and verify if it detects ");
  Serial.print("the correct approximated distance.\n\n");
}
/*
 * Function which serves as the 'main' of this porgram, it will ask the user two (2) questions with the aid of the Serial Monitor. The
 * first one is associate with the unit of length meassurement, and the other to that of the undertaking of the tests to obtain the values
 * for the construction of the equation of the line.
 */
void loop() {
  static bool answered = false;
  static bool testEnable = false;
  static String unit = "";
  if(answered == false){
    Serial.println("What will be the unit of distance measurement?");
    do{
      if(Serial.available() > 0){
        unit = Serial.readStringUntil('\n');
        Serial.flush();
        break;
      }
    }while(1);
    Serial.println(unit);
    Serial.println("Will preliminary tests be undertaken? (yes / no)");
    do{
      if(Serial.available() > 0){
        String tmp = Serial.readStringUntil('\n');
        if(tmp.equals("yes")){
          testEnable = true;
          Serial.println(tmp);
          Serial.flush();
          break;
        }
        else if(tmp.equals("no")){
          Serial.println(tmp);
          Serial.flush();
          break;
        }
        Serial.println("Wrong input! Try again!");
      }
    }while(1);
  }
  answered = true;
  doTests(unit,testEnable);
}
/*
 * Function to accomplish the brunt of functionality that is tasked throughout this experiment. As such, it serves two (2) purposes:
 * 1. If testEnable equals true, then the program will ask for ten (10) different measurements related to the position of the light source, all of which will be outputed on the screen
 * for the user to compile into a graph and its associated equation of the line. It should be noted that the program will go into the
 * power sleep mode state. In other words, the Arduino must be reset.
 * 2. If testEnable equals false, the program will calculate the position of a light source in intervals of fifty (50) meassurements, divided from one another with a delay of 10 seconds. 
 * In this case, the program will run indifinitely.
 */
void doTests(String unit, bool testEnable){
  if(testEnable == true){
    double analogInputAvgs[nTests];
    Serial.println("TEST MODE ENABLED: The Arduino will take ten (10) samples for the magnitude of the average of the input obtained from analogRead(...).\n");
    for(int i = 0; i < nTests; i++){
      Serial.print("SAMPLE ");
      Serial.print(i+1);
      Serial.print(" IN 20 SECONDS! POSITION THE LIGHT SOURCE AT ");
      Serial.print(10*(i+1));
      Serial.print(" ");
      Serial.print(unit);
      Serial.println(" DISTANCE FROM THE PHOTORESISTOR...");
      delay(20000);
      Serial.print("TEST HAS STARTED!... ");
      analogInputAvgs[i] = getAnalogInputAvg();
      Serial.println("TEST HAS COMPLETED!");
    }
    Serial.println("\nTESTS COMPLETED! PLEASE MAKE A NOTE OF THE OBTAINED VALUES SO AS TO CALCULATE THE EQUATION OF THE GRAPH!The results are as follows: ");
    for(int i = 0; i < nTests; i++){
      Serial.print(i+1);
      Serial.print(". ");
      Serial.println(analogInputAvgs[i]);
    }
    Serial.print("\n\n\nARDUINO WILL GO TO POWER DOWN SLEEP MODE! IF WANT TO START THE PROGRAM AGAIN, RESET THE DEVICE.");
    powerDownSleep();
  }
  else{
    static unsigned long int i = 0;
    if( i == 0){
      Serial.println("TEST MODE DISABLED: The Arduino will try to approximate the distance of the light source from the photoresistor."); 
    }
    Serial.print("For distance measurement number ");
    Serial.print(i+1);
    Serial.print(", the aproximated distance is ");
    Serial.print(getAproxDistance((double)analogRead(pinA)));
    Serial.print(" ");
    Serial.println(unit);  
    i++;
    if(i % 50 == 0){
      Serial.println("\n\n\nFIFTY MEASUREMENTS HAVE BEEN COMPLETED! ARDUINO WILL RESTART TAKING THEM IN 10 SECONDS!\n");
      delay(10000);
      i = 0;
    }
  }  
}
/*
 * The getAnalogInputAvg() calculates the average of the sum of the analogReads of pin A13. This value is to be associated
 * with the approximated distance.
 */
double getAnalogInputAvg(){
  long int sum = 0;
  for(int i = 0; i < nIterations; i++){
    sum = sum + analogRead(pinA);
  }
  return ((double)sum)/((double)nIterations);
}
/*
 * The function getAproxDistance(...) tackles with the equation of the graph that is used to approximate the various
 * distances of the light source. Furthermore, as a parameter, it has aRead which is the same as the value obtained
 * from pin A13.
 */
double getAproxDistance(double aRead){
  return 709*pow(aRead,-0.665);
}
/*
 * The following function, when called, makes the program enter some form of power down sleep sate.
 */
void powerDownSleep(){
  while(1){};
}

/*
void loop(){
  for(int i = 0; i < nIterations; i++){
    double voltageA13 = analogRead(A13)*(5.0/1024);
    double a13Temp = (900/5)*(voltageA13-0.5);
    double lux = k*pow(a13Temp,4);
    //double lux = 500*(5.0/voltageA13 - 1)/R;
    double distance = sqrt(L/(4*PI*lux))*100;
    sumDistances = sumDistances + distance;
  }
  Serial.println(sumDistances/((double)nIterations));
  delay(5000); 
}
*/
