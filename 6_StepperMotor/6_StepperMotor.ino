const int IN1 = 22;                                                     // Pin IN1 of Stepper Motor.
const int IN2 = 23;                                                     // Pin IN2 of Stepper Motor.
const int IN3 = 24;                                                     // Pin IN3 of Stepper Motor.
const int IN4 = 25;                                                     // Pin IN4 of Stepper Motor.
const int MAXSTEPS = 4096;                                              // Maximum value of steps for one (1) Stepper Motor's rotation.

String command = "";                                                    // Variable to hold a string which will represent a command in order to control the motor.
short iStep = 0;                                                        // Variable to hold the actual number of steps that the mottor has done for a particular moment in time.

// 1 -> counterclockwise and -1 -> clockwise
 
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  
  Serial.println("STEPPER ROTATION PROGRAM");
  Serial.println("------------------------");
  Serial.println("This program uses the following series of commands to control a STEPPER MOTOR:");
  Serial.println("1. CW: Specifies the motor to rotate in clocwise fashion indefinitely.\nUSAGE EXAMPLE: CW\n");
  Serial.println("2. CC: Specifies the motor to rotate in counter-clocwise fashion indefinitely.\nUSAGE EXAMPLE: CC\n");
  Serial.println("3. STP: Specifies the motor to rotate for a n number of steps. Furthermore these steps can be either positive or negative.\nUSAGE EXAMPLE: STP 1000\n");
  Serial.println("4. CCC: Sets the motor to rotate clockwise for a n number of times.\nUSAGE EXAMPLE: CCC 10\n");
  Serial.println("5. CCW: Sets the motor to rotate counter-clockwise for a n number of times.\nUSAGE EXAMPLE: CCW 20\n");
  Serial.println("6. CSC: Sets the motor to rotate clockwise for a n amount of steps.\nUSAGE EXAMPLE: CSC 2048\n");
  Serial.println("7. CSW: Sets the motor to rotate counter-clockwise for a n amount of steps.\nUSAGE EXAMPLE: CSW 10000\n");
  Serial.println("8. STOP: Interrupts the program.\nUSAGE EXAMPLE: STOP\n");
}

void loop() {
  if(Serial.available()>0){                                           // Condition to check if the is input in the Serial.
    terminalMode();                                                   // Function to control the motor given the input.                                                 
  }
}

void terminalMode(){
  command = Serial.readStringUntil('\n');                             // Assign the contents of the Serial input to varible "command".
  Serial.flush();                                 
  
  if(command.equals("CW")){                                           // If command = "CW", then the stepper motor will rotate in clockwise direction until another key(s) is pressed. 
    do{
      rotate(-1);                                                     // Function to rotate Stepper Motor.
    }while(Serial.available()<=0);
  }

  else if(command.equals("CC")){                                      // If command = "CC", then the stepper motor will rotate in counterclockwise direction until another key(s) is pressed.
    do{
      rotate(1);
    }while(Serial.available()<=0);
  }
  
  else if(command.substring(0,3).equals("STP")){                      // If command = "STP", then the stepper motor will rotate for a definite number of steps in any direction.
    long int realSteps = abs(command.substring(3).toInt());           // Example Usage: STP 4096 should rotate motor 360 degrees one time clockwise. If value is negative,
    short k = command.substring(3).toInt() / realSteps;               // the opposite is true.
    for(int i = 0; i < realSteps;){                                   // Anyhow: realSteps is the magnitude of the # of steps, and k will decide the direction of rotation.
      if(rotate(-1*k)){
        i++;
      }
      if(isSTOP()){
        goto exit;
      }
    }
  }
  else if(command.substring(0,3).equals("CCC")){                      // If command = "CCC", then the stepper motor will rotate for a definite number of times clockwise.
    long int realRots = abs(command.substring(3).toInt());            // Example Usage: CCC 3 will make the motor rotate 3 times in clockwise direction.
    for(long int i = 0; i < realRots; i++){                           // realRots is the magnitude of the # of rotations. As with realSteps, realRots is an absolute value
      for(int j = 0; j < MAXSTEPS;){                                  // in order to deal with negative (erronous) values.
        if(rotate(-1)){
          j++; 
        }
        if(isSTOP()){
          goto exit;
        }
      }
    }
  }
  else if(command.substring(0,3).equals("CCW")){                      // If command = "CCW", then the stepper motor will rotate for a definite number of times counter-clockwise.
    long int realRots = abs(command.substring(3).toInt());
    for(long int i = 0; i < realRots; i++){
      for(int j = 0; j < MAXSTEPS;){
        if(rotate(1)){
          j++;
        }
        if(isSTOP()){
          goto exit;
        }
      }
    }
  }
  else if(command.substring(0,3).equals("CSC")){                      // If command = "CSC", then the stepper motor should rotate for a definite number of steps clockwise.
    long int realSteps = abs(command.substring(3).toInt());
    for (long int i = 0; i < realSteps;){
      if(rotate(-1)){
        i++;
      }
      if(isSTOP()){
        goto exit;
      }
    }
  }
  else if(command.substring(0,3).equals("CSW")){                     // If command = "CSW", then the motor should rotate for a definite number of steps counter-clockwise.
    long int realSteps = abs(command.substring(3).toInt());
    for (long int i = 0; i <realSteps;){
      if(rotate(1)){
        i++;
      }
      if(isSTOP()){
        goto exit;
      }
    }
  }
  else if(command.equals("STOP")){
    goto exit;
  }
  
  exit:
  Serial.flush();
}

bool isSTOP(){                                                      // Function to check if "STOP" was wriiten on the Serial port.
  String tmp = "";                                                  // tmp variable for string of Serial port input
  if(Serial.available()>0){                                         // If condition to check wether there is information on Serial port, if so read such information until '\n' is found.
    tmp = Serial.readStringUntil('\n');
  }
  if(tmp.equals("STOP")){                                           // If "STOP" is what was written on the Serial port, return true.
    return true;
  }
  return false;                                                     // Otherwise, resturn false.
}
bool rotate(short clockwiseConstant){                                // Function to enable the rotation of the stepper motor for one step in a particular direction. 
  static unsigned long currentTime, lastTime = 0;                    // If parameter clockwiseConstant is '-1', the motor will rotate in clockwise direction; the opposite
  static long time;                                                  // is true.
  currentTime = micros();                                            // It requires timming variables (currentTime, lastTime, time) in order to rotate.
  if(currentTime-lastTime>=1000){                                    // It returns true if the motor is able to rotate.
    stepper(clockwiseConstant);
    time = time + (micros() - lastTime);
    lastTime = micros();
    return true;
  }
  return false;
}

void stepper(short clockwiseConstant){                                // Function physically control the steps (rotation) of the stepper motor.
  iStep = iStep + clockwiseConstant;
  if(iStep < 0 && clockwiseConstant == -1){
    iStep = 7;
  }
  if(iStep > 7 && clockwiseConstant == 1){
    iStep = 0;
  }
  switch(iStep){
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
}
