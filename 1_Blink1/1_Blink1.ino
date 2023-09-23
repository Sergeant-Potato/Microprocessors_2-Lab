// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  /*
   * --------------------------------------------------
   * This is the Original Version of the Blink Program
   * --------------------------------------------------
   * digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   * delay(1000);                       // wait for a second
   * digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   * delay(1000);                       // wait for a second
   */

  /*
   * The following lines of code generate the wanted functionality of the first stage of the extepriment of this report; that is, to make the LED blink in longer increments. In other words:
   * First On / Off Blink => 1000ms or 1s each
   * Second On / Off Blink => 2000ms or 2s each
   * Third On / Off Blink => 3000ms or 3s each
   * ...
   * Ninth On / Off Blink => 9000ms or 9s each
   * Tenth On / Off Blink => 10000ms or 10s each
   * 
   * The FOR contains a variable i which will initially hold the value of 1000 (ns or 1s). This value is then incremented by 1000 at each FOR iteration until it becomes larger than, well, 10000 (ns or 10s).
   */
  for (int i=1000;i<=10000;i+= 1000){
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
    delay(i);                           // wait for i seconds
    digitalWrite(LED_BUILTIN, LOW);     // turn the LED off by making the voltage LOW
    delay(i);                           // wait for i seconds
  }
}
