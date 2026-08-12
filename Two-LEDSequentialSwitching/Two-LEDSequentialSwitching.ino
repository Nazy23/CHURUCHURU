int buttonPin = 2;
int led1 = 13;
int led2 = 12;
int buttonState = 1;
int lastButtonState = HIGH;
int mode = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    mode++;

    if (mode > 2) {
      mode = 0;
    }

    delay(200);
  }

  lastButtonState = buttonState;

  switch (mode) {
    case 0:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      break;

    case 1:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      break;

    case 2:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      break;
  }
}