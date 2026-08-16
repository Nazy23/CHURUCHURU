int potValue = 0;
int ledLevel = 0;

int leds[] = {2, 3, 4, 5, 6};

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Read the potentiometer
  potValue = analogRead(A0);

  // Convert 0-1023 into 0-5
  ledLevel = map(potValue, 0, 1023, 0, 5);

  // Control the LEDs
  for (int i = 0; i < 5; i++) {

    if (i < ledLevel) {
      digitalWrite(leds[i], HIGH);
    }
    else {
      digitalWrite(leds[i], LOW);
    }
  }

  // Display the values in Serial Monitor
  Serial.print("Potentiometer: ");
  Serial.print(potValue);

  Serial.print(" | LEDs: ");
  Serial.println(ledLevel);

  delay(50);
}
