void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
   digitalWrite(12, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
   digitalWrite(11, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
   digitalWrite(10, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
  digitalWrite(13, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  digitalWrite(12, LOW);  // change state of the LED by setting the pin to the HIGH voltage level
  digitalWrite(11, LOW);  // change state of the LED by setting the pin to the HIGH voltage level
  digitalWrite(10, LOW);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(500);                      // wait for a second
}