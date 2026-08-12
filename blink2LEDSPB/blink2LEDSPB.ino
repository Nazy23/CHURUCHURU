int led1=13;
int led2=12;
int button=2;

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT);
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