// MOTOR PINS

int motor1pin1 = 8;    // LEFT MOTOR
int motor1pin2 = 9;

int motor2pin1 = 10;   // RIGHT MOTOR
int motor2pin2 = 11;

// ANALOG IR SENSOR PINS (FLOOR SENSORS)

int leftIR = A0;
int rightIR = A1;

// Adjust this based on your sensor readings
int threshold = 500;

// ULTRASONIC SENSOR PINS

int trigPin = 6;
int echoPin = 7;

// Maximum distance for detecting opponent to Attack
int attackDistance = 50;

void setup() {

  Serial.begin(9600);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  stopLeft();
  stopRight();

  Serial.println("=== SUMOBOT LINE SENSOR + ULTRASONIC ATTACK ===");
}


void loop() {

  // READ LINE SENSORS

  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);

  // READ ULTRASONIC SENSOR

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);

  int distance;

  if (duration == 0) {
    distance = 999;
  }
  else {
    distance = duration * 0.0343 / 2;
  }

  // SERIAL MONITOR FOR TESTING

  Serial.print("LEFT IR: ");
  Serial.print(leftSensor);

  Serial.print(" | RIGHT IR: ");
  Serial.print(rightSensor);

  Serial.print(" | DISTANCE: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ISENSOR LOGIC
  // HIGH VALUE = BLACK
  // LOW VALUE  = WHITE

  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;

  // LINE SENSOR PROTECTION
  // WHITE LINE ALWAYS HAS PRIORITY

  if (!leftBlack && rightBlack) {

    Serial.println("WHITE + BLACK -> LEFT REVERSE / RIGHT STOP");

    leftReverse();
    stopRight();
  }


  else if (leftBlack && !rightBlack) {

    Serial.println("BLACK + WHITE -> LEFT STOP / RIGHT REVERSE");

    stopLeft();
    rightReverse();
  }


  else if (!leftBlack && !rightBlack) {

    Serial.println("WHITE + WHITE -> BOTH REVERSE");

    leftReverse();
    rightReverse();
  }


  // BOTH BLACK
  // SAFE AREA
  // NOW CHECK ULTRASONIC FOR ATTACK

  else if (leftBlack && rightBlack) {

    if (distance <= attackDistance) {

      Serial.println("OPPONENT DETECTED -> BOTH MOTORS FORWARD / ATTACK");

      leftForward();
      rightForward();
    }

    else {

      Serial.println("NO OPPONENT -> RIGHT FORWARD / LEFT STOP");

      stopLeft();
      rightForward();
    }
  }


  delay(50);
}

// LEFT MOTOR

void leftForward() {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
}


void leftReverse() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
}


void stopLeft() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
}

// RIGHT MOTOR

void rightForward() {

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}


void rightReverse() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}


void stopRight() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}