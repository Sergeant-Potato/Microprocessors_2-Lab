/*
 * This is the original code of the professor for one traffic light case!
 * ---------------------------------------------
 * Created by Dr. Roman Lopez.
 * ---------------------------------------------
 */

#define cross 28      // Pin for pedestrain light
#define red 22        // Pin for red light
#define yellow 24     // Pin for yellow light
#define green 26      // Pin for green light
#define button 2      // Pin for pedestrian button
#define delayTime 500 // The delay times to detect the button
// The time-constants for each of the lights
#define greenTime 5
#define yellowTime 3
#define redTime 5

volatile int buttonState = 0; // I think this was not used throughout the code!
int i = 0;  // Varibale to act as the i of the FORs
int flag;   // Flag for interrupt
int lightState;   // The state of the lights of the traffic light

void setup()
{
  pinMode(cross, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);

  attachInterrupt(digitalPinToInterrupt(button), setFlag, LOW); //Attached the Interrupt subroutine
  Serial.begin(9600);
  flag = 0;
}

void loop()
{
LOOP:
  //Set the state flag, 1=green, 2=yellow, 3=red
  //Set green ON, ref and Yellow OFF
  //Green state
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(cross, LOW);
  for (i = 0; i <= greenTime; i++)
  {
    delay(delayTime);
    if (flag == 1)
    {
      lightState = 1;
      Pedestrian();
      goto LOOP;
    }
  }

  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  for (i = 0; i <= redTime; i++)
  {
    delay(delayTime);
    if (flag == 1)
    {
      lightState = 2;
      Pedestrian();
      goto LOOP;
    }
  }

  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  for (i = 0; i <= yellowTime; i++)
  {
    delay(delayTime);
    if (flag == 1)
    {
      lightState = 3;
      Pedestrian();
      goto LOOP;
    }
  }
}
/*
 * Function to set the interrupt flag of the traffic light to 1.
 */
void setFlag(void)
{
  flag = 1;
}
void Pedestrian(void)
{
  switch (lightState)
  {
    case 1: // Case for when traffic light is GREEN.
      {
        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);
        delay(2000);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(cross, HIGH);
        delay(5000);
        break;
      }

    case 2: // Case for when traffic light is YELLOW.
      {
        delay(1500);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(cross, HIGH);
        delay(5000);
        break;
      }

    case 3: // Case for when traffic light is RED.
      {
        digitalWrite(red, HIGH);
        digitalWrite(cross, HIGH);
        delay(3000);
        break;
      }

    default : {};
  }

  for (i = 0; i <= 5; i++) // For to turn on and off intermitently the pedestrian light for 1 second each time.
  {
    digitalWrite(cross, LOW);
    delay(1000);
    digitalWrite(cross, HIGH);
    delay(1000);
  }
  flag = 0; // Reset the interrupt flag of the predestrian.
}
