// Ultrasonic Distance LED Indicator
// Maximum detection distance: 12 inches

int distance = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);

  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);

  // LED pins
  pinMode(13, OUTPUT);  // Green
  pinMode(12, OUTPUT);  // Yellow
  pinMode(11, OUTPUT);  // Red
}

void loop()
{
  long duration = readUltrasonicDistance(6, 5);

  // Turn all LEDs OFF first
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);

  // No object detected
  if (duration == 0)
  {
    Serial.println("No object detected");
  }

  else
  {
    // Convert echo time to inches
    distance = duration / 148;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" inches");

    // FAR: 9–12 inches
    if (distance >= 9 && distance <= 12)
    {
      digitalWrite(13, HIGH);
    }

    // MIDDLE: 5–8 inches
    else if (distance >= 5 && distance < 9)
    {
      digitalWrite(12, HIGH);
    }

    // NEAR: 1–4 inches
    else if (distance >= 1 && distance < 5)
    {
      digitalWrite(11, HIGH);
    }

    // More than 12 inches
    else
    {
      // All LEDs remain OFF
    }
  }

  delay(100);
}
