int delayTime = (1500); // indicator of delay

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(delayTime);                      // wait for a second
  digitalWrite(2, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(delayTime);                      // wait for a second
}
