// ==================================================
// SUMOBOT
// LINE SENSOR + ULTRASONIC ATTACK
// ADJUSTABLE NORMAL SPEED + ATTACK SPEED
// ==================================================


// ===============================
// MOTOR PINS
// ===============================

int motor1pin1 = 8;    // LEFT MOTOR
int motor1pin2 = 9;

int motor2pin1 = 10;   // RIGHT MOTOR
int motor2pin2 = 11;


// ===============================
// ENA / ENB SPEED PINS
// ===============================

int ENA = 5;    // LEFT MOTOR SPEED
int ENB = 3;    // RIGHT MOTOR SPEED


// ===============================
// SPEED SETTINGS
// ===============================

// Normal movement / searching speed
int motorSpeed = 200;

// Attack speed
// 255 = maximum 
int attackSpeed = 255;


// ===============================
// ANALOG IR SENSOR PINS
// ===============================

int leftIR = A0;
int rightIR = A1;

// Adjust based on your sensor readings
int threshold = 500;


// ===============================
// ULTRASONIC SENSOR PINS
// ===============================

int trigPin = 6;
int echoPin = 7;

// Opponent detection distance
int attackDistance = 75;


// ===============================
// SETUP
// ===============================

void setup() {

  Serial.begin(9600);

  // Motor pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // ENA / ENB
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Stop motors at startup
  stopLeft();
  stopRight();

  Serial.println("=================================");
  Serial.println("SUMOBOT READY");
  Serial.println("LINE SENSOR + ULTRASONIC ATTACK");
  Serial.println("=================================");

  Serial.print("Normal Speed: ");
  Serial.println(motorSpeed);

  Serial.print("Attack Speed: ");
  Serial.println(attackSpeed);
}


// ===============================
// MAIN LOOP
// ===============================

void loop() {

  // =================================
  // READ LINE SENSORS
  // =================================

  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);


  // =================================
  // READ ULTRASONIC
  // =================================

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);

  int distance;

  if (duration == 0) {

    distance = 999;

  } else {

    distance = duration * 0.0343 / 2;
  }


  // =================================
  // SERIAL MONITOR
  // =================================

  Serial.print("LEFT IR: ");
  Serial.print(leftSensor);

  Serial.print(" | RIGHT IR: ");
  Serial.print(rightSensor);

  Serial.print(" | DISTANCE: ");
  Serial.print(distance);

  Serial.println(" cm");


  // =================================
  // LINE SENSOR LOGIC
  //
  // HIGH VALUE = BLACK
  // LOW VALUE  = WHITE
  // =================================

  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;


  // ==================================================
  // LEFT WHITE + RIGHT BLACK
  // LEFT REVERSE / RIGHT STOP
  // ==================================================

  if (!leftBlack && rightBlack) {

    Serial.println("WHITE + BLACK -> LEFT REVERSE / RIGHT STOP");

    leftReverse();
    stopRight();
  }


  // ==================================================
  // LEFT BLACK + RIGHT WHITE
  // LEFT STOP / RIGHT REVERSE
  // ==================================================

  else if (leftBlack && !rightBlack) {

    Serial.println("BLACK + WHITE -> LEFT STOP / RIGHT REVERSE");

    stopLeft();
    rightReverse();
  }


  // ==================================================
  // BOTH WHITE
  // BOTH REVERSE
  // ==================================================

  else if (!leftBlack && !rightBlack) {

    Serial.println("WHITE + WHITE -> BOTH REVERSE");

    leftReverse();
    rightReverse();
  }


  // ==================================================
  // BOTH BLACK
  // SAFE AREA
  // CHECK ULTRASONIC
  // ==================================================

  else if (leftBlack && rightBlack) {

    // =================================
    // OPPONENT DETECTED
    // ATTACK!
    // =================================

    if (distance <= attackDistance) {

      Serial.println("OPPONENT DETECTED -> MAXIMUM ATTACK!");

      attackForward();
    }


    // =================================
    // NO OPPONENT
    // ORIGINAL SEARCHING BEHAVIOR
    // =================================

    else {

      Serial.println("NO OPPONENT -> SEARCHING");

      stopLeft();
      rightForward();
    }
  }


  delay(50);
}


// ==================================================
// LEFT MOTOR
// ==================================================


// LEFT FORWARD

void leftForward() {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  analogWrite(ENA, motorSpeed);
}


// LEFT REVERSE

void leftReverse() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  analogWrite(ENA, motorSpeed);
}


// LEFT STOP

void stopLeft() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  analogWrite(ENA, 0);
}


// ==================================================
// RIGHT MOTOR
// ==================================================


// RIGHT FORWARD

void rightForward() {

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  analogWrite(ENB, motorSpeed);
}


// RIGHT REVERSE

void rightReverse() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  analogWrite(ENB, motorSpeed);
}


// RIGHT STOP

void stopRight() {

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  analogWrite(ENB, 0);
}


// ==================================================
// MAXIMUM ATTACK
// ==================================================

void attackForward() {

  // LEFT MOTOR FORWARD
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  // RIGHT MOTOR FORWARD
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  // ATTACK SPEED
  analogWrite(ENA, attackSpeed);
  analogWrite(ENB, attackSpeed);
}