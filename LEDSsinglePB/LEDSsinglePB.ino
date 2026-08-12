// C++ code
//
int buttonState = 0;

void setup()
{
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(7);
  if (buttonState == HIGH); {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}