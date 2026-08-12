// C++ code
//
int buttonState = 0;
int delayTime = 500;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
    delay(delayTime); // Wait for 1000 millisecond(s)
    digitalWrite(13,LOW);
    digitalWrite(12, HIGH);
    delay(delayTime); // Wait for 1000 millisecond(s)
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    delay(delayTime); // Wait for 1000 millisecond(s)
    digitalWrite(11, LOW);

  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
}