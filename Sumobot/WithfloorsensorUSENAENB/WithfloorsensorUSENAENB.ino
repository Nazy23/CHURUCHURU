/*

TEAM DREAM SUMOBOT
ROBOT NAME: 

MEMBERS:
Ann Arcalas
Nataniel Mapa
Nazren Sorio

Wires Connection Color code

MOTOR PINS
EN1 white
EN2 green
EN3 blue
EN4 violet

ENA orange
ENB brown

FLOOR SENSOR
leftIR yellow
rightIR yellow

SIDES SENSOR
left
right

BACK SENSOR 
==============================
*/

// MOTOR PINS

int motor1pin1 = 8;    // LEFT MOTOR EN1 white
int motor1pin2 = 9;    // EN2 green

int motor2pin1 = 10;   // RIGHT MOTOR EN3 blue
int motor2pin2 = 11;   // EN4 violet

// ENA / ENB SPEED PINS

int ENA = 5;    // LEFT MOTOR SPEED, orange
int ENB = 3;    // RIGHT MOTOR SPEED, brown

// SPEED SETTINGS

int motorSpeed = 255;
int attackSpeed = 255;

// FLOOR SENSOR PINS

int leftIR = A0; // yellow
int rightIR = A1; // yellow 

int threshold = 500;

// ULTRASONIC SENSOR

int trigPin = 6; // purple
int echoPin = 7;  // brown

int attackDistance = 75;

// U-TURN SETTINGS

// How long the robot reverses before turning
int reverseTime = 500;

// How long the robot turns
int turnTime = 400;

// SETUP

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

  stopLeft();
  stopRight();

  Serial.println("=== SUMOBOT READY ===");
}

// MAIN LOOP

void loop() {

  // READ FLOOR SENSORS
 
  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);

  // READ ULTRASONIC

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


  // =================================
  // SENSOR LOGIC
  // BLACK = SAFE
  // WHITE = EDGE
  // =================================

  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;

  // SERIAL MONITOR

  Serial.print("LEFT: ");
  Serial.print(leftSensor);

  Serial.print(" | RIGHT: ");
  Serial.print(rightSensor);

  Serial.print(" | DISTANCE: ");
  Serial.print(distance);

  Serial.println(" cm");

  // LEFT SENSOR DETECTS WHITE
  // U-TURN TO THE RIGHT

  if (!leftBlack && rightBlack) {

    Serial.println("LEFT WHITE -> U-TURN RIGHT");

    // First move away from edge
    leftReverse();
    rightReverse();

    delay(reverseTime);

    // Turn RIGHT
    leftForward();
    rightReverse();

    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // RIGHT SENSOR DETECTS WHITE
  // U-TURN TO THE LEFT

  else if (leftBlack && !rightBlack) {

    Serial.println("RIGHT WHITE -> U-TURN LEFT");

    // First move away from edge
    leftReverse();
    rightReverse();

    delay(reverseTime);

    // Turn LEFT
    leftReverse();
    rightForward();

    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // BOTH SENSORS DETECT WHITE
  // REVERSE THEN TURN

  else if (!leftBlack && !rightBlack) {

    Serial.println("BOTH WHITE -> REVERSE + U-TURN");

    // Move away from edge
    leftReverse();
    rightReverse();

    delay(reverseTime);

    // Turn around
    leftForward();
    rightReverse();

    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // BOTH BLACK = SAFE

  else if (leftBlack && rightBlack) {

    // OPPONENT DETECTED

    if (distance <= attackDistance) {

      Serial.println("OPPONENT DETECTED -> ATTACK!");

      attackForward();
    }

    // SEARCHING FOR OPPONENT

    else {

      Serial.println("NO OPPONENT -> SEARCHING");

      stopLeft();
      rightForward();
    }
  }

  delay(30);
}

// LEFT MOTOR

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


void stopLeft() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  analogWrite(ENA, 0);
}

// RIGHT MOTOR

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


void stopRight() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  analogWrite(ENB, 0);
}

  // ATTACK FORWARD

void attackForward() {

  // LEFT MOTOR
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  // RIGHT MOTOR
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  // MAXIMUM ATTACK SPEED
  analogWrite(ENA, attackSpeed);
  analogWrite(ENB, attackSpeed);
}
