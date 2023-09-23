/*
 * The following LEDs and pins are related to one-another:
 * RED1     ->      22
 * RED2     ->      23
 * YELLOW1  ->      24
 * YELLOW2  ->      25
 * GREEN1   ->      26
 * GREEN2   ->      27
 * CROSS1   ->      28
 * CROSS2   ->      29
 * 
 * Moreover, the following pins are related to the one 7-Segment Display
 * A -> 30
 * B -> 31
 * C -> 32
 * D -> 33
 * E -> 34
 * F -> 35
 * G -> 36
 */

const int button1 = 2;                                  // Pin of button for traffic light 1
const int button2 = 3;                                  // Pin of button for reaffuc light 2
const int tSize = 4;                                    // The size of each of the arrays for the number of lights of each traffic light
const int trafficA[] = {22, 24, 26, 28};                // Traffic Light A lights
const int trafficB[]= {23, 25, 27, 29};                 // Traffic Light B Lights
const int sevenSeg[] = {30, 31, 32, 33, 34, 35, 36};    // ADDED: Seven Segment Pins
const int timmings[] = {5, 3, 5};                       // The constant of timmings for each of the lights: RED, YELLOW and GREEN, respectively.

int state = 1;                                          // Variable to know which light is the program currently on
bool atFirst = true;                                    // Variable to know which of the two (2) traffic lights is currently being used; i.e.: changing colors.
int flag1 = 0;                                          // Interrupt Flag for traffic 1
int flag2 = 0;                                          // Interrupt Flag for traffic 2

void setup() {
  /*
   * FOR to set the pin mode of all the pins of the two (2) traffic lights LEDs. With that being said, since they are LEDs, they are set to be OUTPUTS.
   */
  for(int i = 0; i<tSize;i++){
    pinMode(trafficA[i],OUTPUT);
    pinMode(trafficB[i],OUTPUT);
  }
  for(int i = 0; i <7; i++){
    pinMode(sevenSeg[i], OUTPUT);
  }
  pinMode(button1, INPUT);                              // Setting pin mode of the pin of button 1 to INPUT since its, well, a button.
  pinMode(button2, INPUT);                              // Setting pin mode of the pin of button 2 to INPUT.
  attachInterrupt(digitalPinToInterrupt(button1),setFlag1,LOW);   // Attached the Interrup subroutine. It is LOW per professor's instructions; hence, oposite button will activate this interrupt. 
  attachInterrupt(digitalPinToInterrupt(button2),setFlag2,LOW);   // Same as above, but for button 2.
  Serial.begin(9600);
  construct();                                          // Call of function to set all LEDS to OFF state. (Initial State)
  sevenDisplay(0);
}

void loop() {
  changeStateTA();                                      // Call of function to tackle with the changing of traffic 1 lights. This does not include when the pedestrian light is on.
  changeStateTB();                                      // Call of function to tackle with the changing of traffic 2 lights. This does not include when the pedestrian light is on.
  waitIntv();                                           // Call of function to wait some interval of time depending on the current light-states of the traffic lights.
  /*
   * If condition to check if state is not equal to zero; that is, an interrupt hasn't occured. Don't want to jump states!
   */
  if(state != 0){
    state = state + 1;
  }
  /*
   * If state is greater than three (3); that is, all three states have already been completer for one of the traffic lights (or a Interrupt has occured), then reset the state variable to 1 and invert atFirst.
   */
  if(state > 3){
    state = 1;
    atFirst = !atFirst;
  }
}
/*
 * Function to set the value of flag1 to 1
 */
void setFlag1(void){
  flag1 = 1;
}
/*
 * Function to set the value of flag2 to 1
 */
void setFlag2(void){
  flag2 = 1;
}
/*
 * Function to do the initial case for all the traffic lights; that is, to deactivate all of the LEDS if activated previously.
 */
void construct(void){
  for(int i = 0; i < tSize; i++){
    digitalWrite(trafficA[i],LOW);
  }
  for(int i = 0; i < tSize; i++){
    digitalWrite(trafficB[i],LOW);
  }
}
/*
 * Function to change the current light of traffic light 1; hence:
 *  If atFirst = true, then the light state (the current activated light) will change for the traffic light 1.
 *  If the opposite is true, the traffic light will have the RED light on.
 */
void changeStateTA(void){
  if(atFirst==true){
    if(state != 1){
      digitalWrite(trafficA[tSize-state],LOW);  // Deactivate the previous activated light. (If green is on in state 1, then in state 2 it must be deactivated.
    }
    else{
      digitalWrite(trafficA[0],LOW);  // Deactivate RED light since it will be on by state 1.
    }
    digitalWrite(trafficA[tSize-state-1],HIGH); // Activate current state light.
  }
  else{
    digitalWrite(trafficA[0], HIGH);  // Activate RED light if the if does not hold.
  }
}
/*
 * This function does the same thing but for traffic light 2. More over, the only difference is that atFirst must be false since only one of the two traffic lights 
 * must be able to change its light state at a time.
 */
void changeStateTB(void){
  if(atFirst==false){
    if(state != 1){
      digitalWrite(trafficB[tSize-state],LOW);
    }
    else{
      digitalWrite(trafficB[0],LOW);
    }
    digitalWrite(trafficB[tSize-state-1],HIGH);
  }
  else{
    digitalWrite(trafficB[0], HIGH);
  }
}

/*
 * Function to enable each of the traffic lights' LEDS be on for a certain interval of time. For instance,
 *  RED and GREEN should be on for 5 seconds.
 *  YELLOW should be on for 3 seconds.
 *  NOTE: This is their normal case; not in their pedestrian alternative!
 */
void waitIntv(void){
  for(int i = 0; i < timmings[state-1];i++){
    delay(1000);                      // 1 second
    if(flag1 == 1 || flag2 == 1){     // If to check if one of the buttons was pressed; that is, if any of the interrupts occurred.
      pedestrianBehavior();           // Pedestrian Function to do when interrupt occurs.
      break;                          // This was the bane of my existance, since I forgot to put it.
    }
  }
}

/*
 * This function does all of the steps necesary for a pedestrain to be able to walk the crosswalk for one of the traffic lights.
 */
void pedestrianBehavior(void){
  if (atFirst == true){             // If to check if the first traffic light was changing its lights colors when one of the buttons was pressed.
    switch(state){
      case 1:                       // Case for when Traffic Light 1 is at GREEN and Traffic Light 2 is at RED
        if(flag2 == 1){
          digitalWrite(trafficB[tSize-1], HIGH);
          delay(timmings[state]*1000);
          break;
        }
        for(int i = tSize-state-1; i>0; i--){
            digitalWrite(trafficA[i],LOW);
            digitalWrite(trafficA[i-1],HIGH);
            if(i == tSize-state-1){
              delay(2000);
            }
        }
        digitalWrite(trafficB[0],LOW);
        digitalWrite(trafficB[tSize-state-1],HIGH);
        digitalWrite(trafficA[tSize-1],HIGH);
        delay(timmings[state]*1000);
        break;
      case 2:                   // Case for when Traffic Light 1 is at YELLOW and Traffic Light 2 is at RED
        delay(timmings[state]*1000/2);
        digitalWrite(trafficA[tSize-state-1],LOW);
        digitalWrite(trafficA[0],HIGH);
        if(flag2 == 1){
          digitalWrite(trafficB[0],LOW);
          digitalWrite(trafficB[tSize-state-1],HIGH);
          digitalWrite(trafficB[tSize-1],HIGH);
          delay(2000);
          digitalWrite(trafficB[tSize-state], LOW);
          digitalWrite(trafficB[tSize-state-1],HIGH);
          delay(2000);
          digitalWrite(trafficB[tSize-state-1],LOW);
          digitalWrite(trafficB[0],HIGH);
          digitalWrite(trafficA[0],LOW);
          digitalWrite(trafficA[tSize-state],HIGH);
          break;
        }
        digitalWrite(trafficA[tSize-1],HIGH);
        digitalWrite(trafficB[0],LOW);
        digitalWrite(trafficB[tSize-state],HIGH);
        delay(5000);
        break;
      case 3:             // Case for when Traffic Light 1 is at RED and Traffic Light 2 is at RED.
        if(flag2 == 1){
          digitalWrite(trafficB[tSize-1],HIGH);
          digitalWrite(trafficB[0],LOW);
          digitalWrite(trafficB[state-1],HIGH);
          delay(2000);
          digitalWrite(trafficB[state-1],LOW);
          digitalWrite(trafficB[tSize-state],HIGH);
          delay(2000);
          digitalWrite(trafficB[tSize-state],LOW);
          digitalWrite(trafficB[0],HIGH);
          digitalWrite(trafficA[0],LOW);
          digitalWrite(trafficA[state-1],HIGH);
          delay(2000);
          break;
        }
        digitalWrite(trafficA[tSize-1],HIGH);
        delay(2000);
        digitalWrite(trafficB[0],LOW);
        digitalWrite(trafficB[state-1],HIGH);
        digitalWrite(trafficA[tSize-1],HIGH);
        delay(2000);
        break;
      default:
      {};
    }  
  }
  else{ // ELSE activate is the second traffic light is changing colors.
    switch(state){
      case 1:       // Case for when Traffic Light 1 is at RED and Traffic Light 2 is at GREEN.
        if(flag2 == 1){
          delay(2000);
          digitalWrite(trafficB[tSize-state-1],LOW);
          digitalWrite(trafficB[state],HIGH);
          delay(2000);
          digitalWrite(trafficB[state],LOW);
          digitalWrite(trafficB[0],HIGH);
          digitalWrite(trafficA[0],LOW);
          digitalWrite(trafficA[tSize-state-1],HIGH);
          digitalWrite(trafficB[tSize-1],HIGH);
          delay(2000);
          break;
        }
        digitalWrite(trafficA[tSize-1],HIGH);
        delay(2000);
        break;
      case 2: // Case for when Traffic Light 1 is at RED and Traffic Light 2 is at YELLOW.
        if(flag2 == 1){
          digitalWrite(trafficB[tSize-1],HIGH);
          delay(2000);
          digitalWrite(trafficB[state-1],LOW);
          digitalWrite(trafficB[0],HIGH);
          digitalWrite(trafficA[0],LOW);
          digitalWrite(trafficA[state],HIGH);
          delay(2000);
          break;
        }
        digitalWrite(trafficA[tSize-1],HIGH);
        delay(1000);
        digitalWrite(trafficB[state-1],LOW);
        digitalWrite(trafficB[0],HIGH);
        digitalWrite(trafficA[0],LOW);
        digitalWrite(trafficA[state],HIGH);
        delay(2000);
        digitalWrite(trafficA[state],LOW);
        digitalWrite(trafficA[state-1],HIGH);
        delay(20000);
        digitalWrite(trafficA[state-1],LOW);
        digitalWrite(trafficA[0],HIGH);
        digitalWrite(trafficB[0],LOW);
        digitalWrite(trafficB[state],HIGH);
        delay(1000);
        break;
      case 3: // Case for when Traffic Light 1 is at RED and Traffic Light 2 is at RED.
        if(flag2 ==1){
          digitalWrite(trafficB[state],HIGH);
          delay(1000);
          digitalWrite(trafficA[0],LOW);
          digitalWrite(trafficA[state-1],HIGH);
          delay(1000);
          break;
        }
        digitalWrite(trafficA[state],HIGH);
        delay(1000);
        digitalWrite(trafficA[0],LOW);
        digitalWrite(trafficA[state-1],HIGH);
        delay(2000);
        digitalWrite(trafficA[state-1],LOW);
        digitalWrite(trafficA[tSize-state],HIGH);
        delay(2000);
        digitalWrite(trafficA[tSize-state],LOW);
        digitalWrite(trafficA[0],HIGH);
        digitalWrite(trafficB[0],LOW);
        digitalWrite(trafficB[state-1],HIGH);
        break;
      default:
      {};
    }
  }
  /*
   * If and else statments to activate intermitently the pedestrian lights of traffic light 1 and 2, respectively.
   */
  if(flag1 ==1){
    for(int i = 0; i<5;i++){
      digitalWrite(trafficA[tSize-1],LOW);
      sevenDisplay(9-2*i);
      delay(1000);
      digitalWrite(trafficA[tSize-1],HIGH);
      sevenDisplay(9-2*(i+1)+1);
      delay(1000);
    }
  }
  else{
    for(int i = 0; i<5;i++){
      digitalWrite(trafficB[tSize-1],LOW);
      sevenDisplay(9-2*i);
      delay(1000);
      digitalWrite(trafficB[tSize-1],HIGH);
      sevenDisplay(9-2*(i+1)+1);
      delay(1000);
    }
  }
  /*
   * IF to reset traffic light 1 whenever its button was pressed.
   */
  if(flag1 == 1){
    digitalWrite(trafficA[tSize-1],LOW);
    digitalWrite(trafficB[2],LOW);
    digitalWrite(trafficB[1],HIGH);
    delay(1000);
    digitalWrite(trafficB[1],LOW);
    digitalWrite(trafficB[0],HIGH);
  }
  else{
    digitalWrite(trafficB[tSize-1],LOW); // This else statment may be deprecated, but there seems to be no change in the functionality of the program.
  }
  flag1 = 0;      // Reset flag 1
  flag2 = 0;      // Reset flag 2
  state = 4;      // Set state to be greater than 3 so to reset it later on in the loop function
  atFirst = false;  // Set atFirst to false to invert it later on.
}
void sevenDisplay(int number){
  switch(number){
    case 0:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], LOW);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], HIGH);
      break;
    case 1:
      digitalWrite(sevenSeg[0], HIGH);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], HIGH);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], HIGH);
      digitalWrite(sevenSeg[6], HIGH);
      break;
    case 2:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], HIGH);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], LOW);
      digitalWrite(sevenSeg[5], HIGH);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 3:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], HIGH);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 4:
      digitalWrite(sevenSeg[0], HIGH);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], HIGH);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 5:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], HIGH);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 6:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], HIGH);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], LOW);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 7:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], HIGH);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], HIGH);
      digitalWrite(sevenSeg[6], HIGH);
      break;
    case 8:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], LOW);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], LOW);
      break;
    case 9:
      digitalWrite(sevenSeg[0], LOW);
      digitalWrite(sevenSeg[1], LOW);
      digitalWrite(sevenSeg[2], LOW);
      digitalWrite(sevenSeg[3], LOW);
      digitalWrite(sevenSeg[4], HIGH);
      digitalWrite(sevenSeg[5], LOW);
      digitalWrite(sevenSeg[6], LOW);
      break;
    default:{};
  }
}
