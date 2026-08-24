// C++ code
//
int buttonState = 0;

int val = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
}

void loop()
{
  val = 0.01723 * readUltrasonicDistance(33, 32);
  Serial.println(val);
  // it shows the value of how much is the distance
  // from sensor
  if (val <= 299 && val >= 200) {
    digitalWrite(15, HIGH);
  } else {
    digitalWrite(15, LOW);
  }
  if (val <= 199 && val >= 100) {
    // <,> symbol is to indicate the min-max of
    // distance detected
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  if (val <= 99 && val >= 1) {
    digitalWrite(0, HIGH);
  } else {
    digitalWrite(0, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}