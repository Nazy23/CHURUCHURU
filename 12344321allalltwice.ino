// LED pins
const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;

// Push button pin
const int BUTTON = 4;

int sequence = 0;
int lastButtonState = HIGH;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  // Turn all LEDs OFF
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {

  int buttonState = digitalRead(BUTTON);

  // Detect button press
  if (lastButtonState == HIGH && buttonState == LOW) {

    sequence++;

    // Return to sequence 1 after sequence 4
    if (sequence > 4) {
      sequence = 1;
    }

    // Sequence 1
    if (sequence == 1) {

      digitalWrite(LED1, LOW);
      digitalWrite(LED1, HIGH);
      delay(200);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED1, LOW);
      delay(200);

      digitalWrite(LED2, LOW);
      digitalWrite(LED2, HIGH);
      delay(200);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED2, LOW);
      delay(200);
      
      digitalWrite(LED3, LOW);
      digitalWrite(LED3, HIGH);
      delay(200);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED3, LOW);
      delay(200);

      digitalWrite(LED4, LOW);
      digitalWrite(LED4, HIGH);
      delay(200);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED4, LOW);
      delay(200);
    }

    // Sequence 2
    else if (sequence == 2) {

      digitalWrite(LED4, LOW);
      digitalWrite(LED4, HIGH);
      delay(200);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED4, LOW);
      delay(200);

      digitalWrite(LED3, LOW);
      digitalWrite(LED3, HIGH);
      delay(200);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED3, LOW);
      delay(200);
      
      digitalWrite(LED2, LOW);
      digitalWrite(LED2, HIGH);
      delay(200);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED2, LOW);
      delay(200);

      digitalWrite(LED1, LOW);
      digitalWrite(LED1, HIGH);
      delay(200);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED1, LOW);
      delay(200);
    }

    // Sequence 3
    else if (sequence == 3) {

      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);

      delay(500);

      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }

    // Sequence 4
    else if (sequence == 4) {

      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);

      delay(300);

      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);

      delay(300);

      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);

      delay(300);

      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);

      delay(300);
    }

    // Button debounce
    delay(200);
  }

  lastButtonState = buttonState;
}