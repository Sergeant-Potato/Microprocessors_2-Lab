const int motorA = 12;                  // Pin for motor A
const int motorB = 13;                  // Pin for motor B
const int k = 20;                       // A constant variable which will determine which values of the speed voltage will be "printed" on the screen

void setup() {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  static bool rotateRight = true;     // Boolean variable to determine if the motor is rotating to the right. If not, it rotates to the left.
  static bool speeding = true;        // Boolean varibale to determine if the motor is speeding up. If not, it is slowing down.
  static bool printed = true;         // Boolean variable to determine if specific values have already been printed on the screen.
  static int motorSpeed = 50;         // Counter variable for the current voltage values at one specific time of the motor.
  static short i = 0;

  /*
   * If condition to output on the screen whenever the motor will rotate to the right. It should be noted that such a message must only be outputed once.
   * Hence:
   *  - rotateRight must be true
   *  - motorSpeed must be equal to the lowest value for which the motor will start to rotate. (It was found to be 50, as in Volts).
   *  - printed must be true since its boolean (Its true for when the motor start to rotate to the right)
   */
  if(rotateRight && motorSpeed == 50 && printed){
    Serial.println("\nThe current direction of the fan is: RIGHT ROTATION.\n");
    printed = false;                  // Variable is set to false so to not output again the message for the time being. 
  }
  /*
   * If condition to output on the screen whenever the motor will rotate to the left. It should be noted that such a message must only be outputed once.
   * Hence:
   *  - rotateRight must be false
   *  - motorSpeed must be equal to the lowest value for which the motor will start to rotate. (It was found to be 50, as in Volts).
   *  - printed must be true since its boolean (Its false for the case in which the motor starts rotating to the left)
   */
  else if(rotateRight == false && motorSpeed == 50 && printed == false){
    Serial.println("\nThe current direction of the fan is: LEFT ROTATION.\n");
    printed = true;
  }
  /*
   * If condition to output both the percentage and its associated voltage usage value of the motor.
   */
  if(i % k == 0){
    float tmp = ((float)(motorSpeed-50)/(205))*100;
    Serial.print("The current speed voltage value (V) of the Fan Motor Usage ");
    Serial.print(i/2);
    Serial.print("% is: ");
    Serial.println(motorSpeed);
  }

  /*
   * If condition to enable the motor to accelerate in either right or left direction. It should be noted that such a motor will accelerate in the range of 50 <= motorSpeed < 250.
   * Furthermore:
   * - The value of 50 comes from the fact that the DC motor needs 50 Volts so to start rotating.
   * - The value of 250 comes from the fact that the DC motor's maximum speed is near the 250 Volts.
   */
  if((motorSpeed >= 50 && motorSpeed < 250) && speeding){
    if(rotateRight){
      analogWrite(motorA, motorSpeed);
      analogWrite(motorB, LOW);
    }
    else{
      analogWrite(motorA, LOW);
      analogWrite(motorB, motorSpeed);
    }
    motorSpeed = motorSpeed + 1;
    i++;
  }
  /*
   * This else if condition follows the same steps of the previous if; however, insetad of accelerating the motor, it just desacelerates it.
   */
  else if((motorSpeed >= 50 && motorSpeed <=250) && speeding == false){
    if(rotateRight){
      analogWrite(motorA, motorSpeed);
      analogWrite(motorB, LOW);
    }
    else{
      analogWrite(motorA, LOW);
      analogWrite(motorB, motorSpeed);
    }
    motorSpeed = motorSpeed - 1;
    i--;
  }
  /*
   * Whenever both of the previous if conditions fail, the motorSpeed and i will be reset to 50 and 0, respectively, and the direction of the motor will become that of its oposite.
   */
  else{
    motorSpeed = 50;
    rotateRight = !rotateRight;
    i = 0;
  }
  /*
   * If condition change the speeding varibale (if the motor will speed up or slow down) whenever the motorSpeed of the motor is either 250 or less than 50.
   */
  if(motorSpeed == 250 || motorSpeed < 50){
    speeding = !speeding;
  }
  delay(50);  // Delay to make motor rotate for more time.
}
