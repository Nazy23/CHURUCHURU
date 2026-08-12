// C++ code
//
int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
