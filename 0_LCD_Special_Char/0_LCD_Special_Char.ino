/*
Arduino 2x16 LCD - LCD Special Char
modified on 18 Feb 2019
by Saeed Hosseini
https://electropeak.com/learn/
*/
#include  <LiquidCrystal.h>
const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int pin_BL = 10; // arduino pin wired to LCD backlight circuit
LiquidCrystal lcd( RS,  EN,  d4,  d5,  d6,  d7);
// smily face
byte smiley[8] = {
 B00000,
 B10001,
 B00000,
 B00000,
 B10001,
 B01110,
 B00000,
};
// Battery sign
byte battery[] = {
 B01110,
 B01010,
 B11011,
 B10001,
 B11111,
 B11111,
 B11111,
 B11111
};
// arrow right
byte R_arrow[8] = {
 B00000,
 B00100,
 B00010,
 B11111,
 B00010,
 B00100,
 B00000,
 B00000
};
// arrow left
byte L_arrow[8] = {
 B00000,
 B00100,
 B01000,
 B11111,
 B01000,
 B00100,
 B00000,
 B00000
};
// Ohm sign 
byte ohm[8] = {
 B00000,
 B01110,
 B10001,
 B10001,
 B10001,
 B01010,
 B11011,
 B00000
};
// Heart
byte heart[8] = {
 B00000,
 B01010,
 B10101,
 B10001,
 B10001,
 B01010,
 B00100,
 B00000
};
int i = 0;
void setup() {
 lcd.begin(16, 2);
 lcd.createChar(0, smiley);
 lcd.createChar(1, battery);
 lcd.createChar(2, R_arrow);
 lcd.createChar(3, L_arrow);
 lcd.createChar(4, ohm);
 lcd.createChar(5, heart);
 lcd.createChar(6, ohm);
 for (int n = 0; n < 6; n++)
 {
   lcd.setCursor(n * 2, 0);
   lcd.write(n);
 }
}
void loop() {
}
