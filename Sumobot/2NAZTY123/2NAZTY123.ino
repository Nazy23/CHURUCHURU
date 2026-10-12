
/*
TEAM DREAM SUMOBOT
ROBOT NAME:

MEMBERS:
Ann Arcalas
Nataniel Mapa
Nazren Sorio

MOTOR WIRE COLORS
EN1 - White
EN2 - Green
EN3 - Blue
EN4 - Violet
ENA - Orange
ENB - Brown

FLOOR SENSORS
Left - A0
Right - A1

OPPONENT SENSORS
Front - Ultrasonic
Left Side - 12
Right Side - 13
Back - A2
*/

// ==============================
// MOTOR PINS
// ==============================

// LEFT MOTOR
int motor1pin1 = 8;
int motor1pin2 = 9;

// RIGHT MOTOR
int motor2pin1 = 10;
int motor2pin2 = 11;

// MOTOR SPEED PINS
int ENA = 5;  // LEFT MOTOR
int ENB = 3;  // RIGHT MOTOR

// MOTOR SPEED: 0 TO 255
int motorSpeed = 200;
int attackSpeed = 255;

// FLOOR SENSOR PINS
int leftIR = A0;
int rightIR = A1;

int threshold = 500;

// ULTRASONIC SENSOR
int trigPin = 6;
int echoPin = 7;

int attackDistance = 25;

// SIDE AND BACK IR SENSORS
int leftSideIR = 12;
int rightSideIR = 13;
int backIR = A2;

// ASSUMPTION: LOW = OPPONENT DETECTED
int opponentDetected = LOW;

// EDGE ESCAPE TIME
int stopTime = 100;
int reverseTime = 300;
int turnTime = 400;

// ==============================
// SETUP
// ==============================

void setup() {

  Serial.begin(9600);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(leftSideIR, INPUT);
  pinMode(rightSideIR, INPUT);
  pinMode(backIR, INPUT);

  digitalWrite(trigPin, LOW);

  stopLeft();
  stopRight();
}

// ==============================
// MAIN PROGRAM
// ==============================

void loop() {

  // READ FLOOR SENSORS
  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);

  // BLACK = SAFE, WHITE = EDGE
  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;

  // READ OPPONENT SENSORS
  bool leftOpponent =
    digitalRead(leftSideIR) == opponentDetected;

  bool rightOpponent =
    digitalRead(rightSideIR) == opponentDetected;

  bool backOpponent =
    digitalRead(backIR) == opponentDetected;

  // READ ULTRASONIC SENSOR
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);

  int distance = 999;

  if (duration > 0) {
    distance = duration * 0.0343 / 2;
  }

  // PRIORITY 1: FLOOR EDGE PROTECTION
  // LEFT BLACK, RIGHT WHITE
  // LEFT MOTOR REVERSE FASTER
  // RIGHT MOTOR REVERSE SLOWER

  if (leftBlack && !rightBlack) {

    Serial.println("RIGHT EDGE - ESCAPE");

    stopLeft();
    stopRight();
    delay(stopTime);

    leftReverse();
    rightReverse();
    delay(reverseTime);

    leftReverseFast();
    rightReverseSlow();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // LEFT WHITE, RIGHT BLACK
  // LEFT MOTOR REVERSE SLOWER
  // RIGHT MOTOR REVERSE FASTER

  else if (!leftBlack && rightBlack) {

    Serial.println("LEFT EDGE - ESCAPE");

    stopLeft();
    stopRight();
    delay(stopTime);

    leftReverse();
    rightReverse();
    delay(reverseTime);

    leftReverseSlow();
    rightReverseFast();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // BOTH FLOOR SENSORS DETECT WHITE

  else if (!leftBlack && !rightBlack) {

    Serial.println("BOTH WHITE - ESCAPE");

    stopLeft();
    stopRight();
    delay(stopTime);

    leftReverse();
    rightReverse();
    delay(reverseTime);

    leftReverseFast();
    rightReverseSlow();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // PRIORITY 2: FRONT OPPONENT
  // BOTH MOTORS ATTACK AT MAXIMUM SPEED

  else if (distance <= attackDistance) {

    Serial.println("FRONT OPPONENT - ATTACK");

    attackForward();
  }

  // PRIORITY 3: LEFT SIDE OPPONENT
  // BOTH MOTORS REVERSE

  else if (leftOpponent) {

    Serial.println("LEFT OPPONENT - REVERSE");

    leftReverse();
    rightReverse();
  }

  // PRIORITY 4: RIGHT SIDE OPPONENT
  // BOTH MOTORS REVERSE

  else if (rightOpponent) {

    Serial.println("RIGHT OPPONENT - REVERSE");

    leftReverse();
    rightReverse();
  }

  // PRIORITY 5: BACK OPPONENT
  // BOTH MOTORS REVERSE

  else if (backOpponent) {

    Serial.println("BACK OPPONENT - REVERSE");

    leftReverse();
    rightReverse();
  }

  // PRIORITY 6: SEARCH FOR OPPONENT
  // LEFT MOTOR STOPPED
  // RIGHT MOTOR MOVES FORWARD

  else {

    Serial.println("SEARCHING");

    stopLeft();
    rightForward();
  }

  delay(30);
}

// ==============================
// LEFT MOTOR FUNCTIONS
// ==============================

void leftForward() {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  analogWrite(ENA, motorSpeed);
}

void leftReverse() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  analogWrite(ENA, motorSpeed);
}

void leftReverseSlow() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  analogWrite(ENA, 100);
}

void leftReverseFast() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  analogWrite(ENA, 255);
}

void stopLeft() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  analogWrite(ENA, 0);
}

// ==============================
// RIGHT MOTOR FUNCTIONS
// ==============================

void rightForward() {

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  analogWrite(ENB, motorSpeed);
}

void rightReverse() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  analogWrite(ENB, motorSpeed);
}

void rightReverseSlow() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  analogWrite(ENB, 100);
}

void rightReverseFast() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  analogWrite(ENB, 255);
}

void stopRight() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  analogWrite(ENB, 0);
}

// ==============================
// ATTACK FUNCTION
// ==============================

void attackForward() {

  // LEFT MOTOR FORWARD
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  // RIGHT MOTOR FORWARD
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  // MAXIMUM SPEED
  analogWrite(ENA, attackSpeed);
  analogWrite(ENB, attackSpeed);
}