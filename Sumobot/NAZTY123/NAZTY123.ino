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
// MOTOR DIRECTION PINS

int motor1pin1 = 8;     // LEFT MOTOR
int motor1pin2 = 9;

int motor2pin1 = 10;    // RIGHT MOTOR
int motor2pin2 = 11;

// MOTOR SPEED PINS

int ENA = 5;            // LEFT MOTOR PWM
int ENB = 3;            // RIGHT MOTOR PWM

// ADJUSTABLE SPEED SETTINGS: 0-255

int motorSpeed = 200;   // Normal movement and side reaction
int attackSpeed = 255;  // Maximum attack PWM

// FLOOR SENSOR PINS
// BLACK = SAFE
// WHITE = EDGE

int leftIR = A0;
int rightIR = A1;

int threshold = 500;

// FRONT ULTRASONIC SENSOR

int trigPin = 6;
int echoPin = 7;

int attackDistance = 25;   // Opponent detection in cm

// SIDE OPPONENT IR SENSORS

int leftSideIR = 12;
int rightSideIR = 13;

// Most digital obstacle IR modules:
// LOW = opponent detected
// HIGH = no opponent
int sideOpponentDetected = LOW;

// EDGE ESCAPE SETTINGS (milliseconds)

int stopTime = 100;
int reverseTime = 300;
int turnTime = 400;

void setup() {

  Serial.begin(9600);

  // Motor direction pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Motor speed control
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Side IR sensors
  pinMode(leftSideIR, INPUT);
  pinMode(rightSideIR, INPUT);

  digitalWrite(trigPin, LOW);

  stopLeft();
  stopRight();

  Serial.print("Normal speed: ");
  Serial.println(motorSpeed);

  Serial.print("Attack speed: ");
  Serial.println(attackSpeed);
}

void loop() {
  // READ FLOOR SENSORS

  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);

  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;

  // READ SIDE OPPONENT SENSORS

  int leftSideReading = digitalRead(leftSideIR);
  int rightSideReading = digitalRead(rightSideIR);

  bool leftOpponent =
    (leftSideReading == sideOpponentDetected);

  bool rightOpponent =
    (rightSideReading == sideOpponentDetected);

  // READ FRONT ULTRASONIC SENSOR

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);

  int distance;

  if (duration == 0) {
    distance = 999;   // No echo received
  }
  else {
    distance = duration * 0.0343 / 2;
  }

  // SERIAL MONITOR

  Serial.print("LEFT FLOOR: ");
  Serial.print(leftSensor);

  Serial.print(" | RIGHT FLOOR: ");
  Serial.print(rightSensor);

  Serial.print(" | FRONT: ");
  Serial.print(distance);
  Serial.print(" cm");

  Serial.print(" | LEFT SIDE: ");
  Serial.print(leftOpponent ? "OPPONENT" : "CLEAR");

  Serial.print(" | RIGHT SIDE: ");
  Serial.println(rightOpponent ? "OPPONENT" : "CLEAR");

  // PRIORITY 1: FLOOR EDGE PROTECTION
  // WHITE = EDGE
  // LEFT FLOOR SENSOR DETECTS WHITE
  // STOP -> REVERSE -> J-TURN RIGHT

  if (!leftBlack && rightBlack) {

    Serial.println("LEFT WHITE -> STOP / REVERSE / J-TURN RIGHT");

    // STEP 1: STOP
    stopLeft();
    stopRight();
    delay(stopTime);

    // STEP 2: REVERSE BOTH MOTORS
    leftReverse();
    rightReverse();
    delay(reverseTime);

    // STEP 3: J-TURN RIGHT
    leftForward();
    rightReverse();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // RIGHT FLOOR SENSOR DETECTS WHITE
  // STOP -> REVERSE -> J-TURN LEFT

  else if (leftBlack && !rightBlack) {

    Serial.println("RIGHT WHITE -> STOP / REVERSE / J-TURN LEFT");

    // STEP 1: STOP
    stopLeft();
    stopRight();
    delay(stopTime);

    // STEP 2: REVERSE BOTH MOTORS
    leftReverse();
    rightReverse();
    delay(reverseTime);

    // STEP 3: J-TURN LEFT
    leftReverse();
    rightForward();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // BOTH FLOOR SENSORS DETECT WHITE
  // STOP -> REVERSE -> J-TURN RIGHT

  else if (!leftBlack && !rightBlack) {

    Serial.println("BOTH WHITE -> STOP / REVERSE / J-TURN");

    // STEP 1: STOP
    stopLeft();
    stopRight();
    delay(stopTime);

    // STEP 2: REVERSE BOTH MOTORS
    leftReverse();
    rightReverse();
    delay(reverseTime);

    // STEP 3: J-TURN RIGHT
    leftForward();
    rightReverse();
    delay(turnTime);

    stopLeft();
    stopRight();
  }

  // PRIORITY 2: OPPONENT DETECTION
  // ONLY WHEN BOTH FLOOR SENSORS SEE BLACK

  else if (leftBlack && rightBlack) {

    // FRONT OPPONENT: ATTACK

    if (distance <= attackDistance) {

      Serial.println("FRONT OPPONENT -> MAXIMUM ATTACK!");

      attackForward();
    }

    // BOTH SIDE SENSORS DETECT OPPONENT

    else if (leftOpponent && rightOpponent) {

      Serial.println("BOTH SIDE OPPONENTS -> BOTH REVERSE");

      leftReverse();
      rightReverse();
    }

    // LEFT SIDE OPPONENT
    // LEFT MOTOR REVERSE
    // RIGHT MOTOR FORWARD

    else if (leftOpponent) {

      Serial.println("LEFT OPPONENT -> LEFT REVERSE");

      leftReverse();
      rightForward();
    }

    // RIGHT SIDE OPPONENT
    // RIGHT MOTOR REVERSE
    // LEFT MOTOR FORWARD

    else if (rightOpponent) {

      Serial.println("RIGHT OPPONENT -> RIGHT REVERSE");

      leftForward();
      rightReverse();
    }


    // --------------------------------
    // NO OPPONENT: SEARCH
    // --------------------------------

    else {

      Serial.println("NO OPPONENT -> SEARCHING");

      stopLeft();
      rightForward();
    }
  }

  delay(30);
}

// LEFT MOTOR CONTROL

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

// RIGHT MOTOR CONTROL

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

// FRONT ATTACK: BOTH MOTORS AT ATTACK SPEED

void attackForward() {

  // LEFT MOTOR FORWARD
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  // RIGHT MOTOR FORWARD
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  // APPLY ATTACK SPEED
  analogWrite(ENA, attackSpeed);
  analogWrite(ENB, attackSpeed);
}