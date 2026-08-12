void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(4, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
  digitalWrite(4, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(0);                      // wait for a second
  digitalWrite(0, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);                      // wait for a second
  digitalWrite(0, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(0);                      // wait for a second
  digitalWrite(2, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
  digitalWrite(2, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(0);                      // wait for a second
}

