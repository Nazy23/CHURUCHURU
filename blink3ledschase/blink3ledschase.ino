int buttonState = 0;

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

// the loop function runs over and over again forever
void loop()
{
  buttonState= digitalRead(2);
  if (buttonState == LOW) {
    digitalWrite (13, LOW);
    digitalWrite (12, LOW);
  } else {
    digitalWrite (13,LOW);
    digitalWrite (12, LOW);
  }

  buttonState= digitalRead(2);
  if (buttonState == HIGH) {
    digitalWrite (13, HIGH);
    digitalWrite (12, HIGH);
  } else {
    digitalWrite (13, LOW);
    digitalWrite (12, LOW);
  }
  delay(10);
}