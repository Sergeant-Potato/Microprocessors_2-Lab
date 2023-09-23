#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // Pins of the Arduino Mega 2560 which will be used.

const int right = 0;                  // Variable to denote when the LCD RIGHT button was pressed.
const int up = 1;                     // Variable to denote when the LCD UP button was pressed.
const int down = 2;                   // Variable to denote when the LCD DOWN button was pressed.
const int left = 3;                   // Variable to denote when the LCD LEFT button was pressed.
const int select = 4;                 // Variable to denote when the LCD SELECT button was pressed.

short int k = 1;                      // Variable denote if the counter will be added or substracted.

void setup() {
  lcd.begin(16,2);                    // Set to use the 16 columns and 2 lines of LCD.
  lcd.setCursor(0,0);                 // Set the cursor of LCD to column and line 0.
  lcd.print("Push LCD Buttons");      // Print the string on upper line of LCD
}

void loop() {
  static long int counter = 0;        // Variable to serve as some counter.
  lcd.setCursor(9,1);                 // Put the LCD cursor on the center of the second line
  lcd.print("       ");               // Erase the last numbers on this section of LCD.

  lcd.setCursor(9,1);                 // Put the LCD cursos on the center of the second line.
  lcd.print(counter/200);             // Print the value of counter at last cursor position.
  
  lcd.setCursor(0,1);                 // Set cursor at the begining of second line
  /*
   * Switch case to detect and print the LCD button pressed. Furthermore:
   *  + If the RIGHT button is pressed, k will be set to 1; hence, the counter will go up after the button is unpressed!
   *  + If the UP button is pressed, counter will be multiplied by 2.
   *  + If the DOWN button is pressed, counter will be divided by 2.
   *  + If the LEFT button is pressed, k will be set to -1; hence, the counter will go down after the button is unpressed!
   *  + If the SELECT button is pressed, counter will reset to 0.
   *  + Initially, counter will go up or down by 1 depending on the value of k.
   */
  switch(getButton()){
    case right:
      lcd.print("RIGHT ");
      k = 1;
      delay(500);
      break;
    case up:
      lcd.print("UP    ");
      counter = 2*counter;
      delay(500);
      break;
    case down:
      lcd.print("DOWN  ");
      counter = counter/2;
      delay(500);
      break;
    case left:
      lcd.print("LEFT  ");
      k = -1;
      delay(500);
      break;
    case select:
      lcd.print("SELECT");
      counter = 0;
      break;
    default:
      lcd.print("      ");
      counter = counter + 1*k;
      break;
  }
}

/*
 * Function to get which button was pressed per the detected sensor values documented in the professor's documentation.
 */
int getButton(){
  int sensor = analogRead(0);

  if(sensor < 50){
    return right;
  }
  else if(sensor >= 50 && sensor < 250){
    return up;
  }
  else if(sensor >= 250 && sensor < 450){
    return down;
  }
  else if(sensor >= 450 && sensor < 650){
    return left;
  }
  else if(sensor >= 650 && sensor < 850){
    return select;
  }
  else{
    return -1;
  }
}
