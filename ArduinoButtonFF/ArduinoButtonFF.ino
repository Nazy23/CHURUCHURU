// C++ code
//
int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);

  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);

  }
  delay(10); // Delay a little bit to improve simulation performance
}