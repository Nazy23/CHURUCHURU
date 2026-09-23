// ===============================
// MOTOR PINS
// ===============================

int motor1pin1 = 8;    // LEFT MOTOR
int motor1pin2 = 9;

int motor2pin1 = 10;   // RIGHT MOTOR
int motor2pin2 = 11;


// ===============================
// ANALOG IR SENSOR PINS
// ===============================

int leftIR = A0;
int rightIR = A1;

// Adjust this based on your sensor readings
int threshold = 500;


void setup() {

  Serial.begin(9600);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  stopLeft();
  stopRight();

  Serial.println("=== ANALOG IR FLOOR SENSOR ===");
}


void loop() {

  int leftSensor = analogRead(leftIR);
  int rightSensor = analogRead(rightIR);


  // ===============================
  // SERIAL MONITOR
  // ===============================

  Serial.print("LEFT IR: ");
  Serial.print(leftSensor);

  Serial.print(" | RIGHT IR: ");
  Serial.println(rightSensor);


  // ===============================
  // INVERTED SENSOR LOGIC
  //
  // HIGH VALUE = BLACK
  // LOW VALUE  = WHITE
  // ===============================

  bool leftBlack = leftSensor > threshold;
  bool rightBlack = rightSensor > threshold;


  // ===============================
  // BOTH BLACK
  // RIGHT = FORWARD
  // LEFT  = STOP
  // ===============================

  if (leftBlack && rightBlack) {

    Serial.println("BLACK + BLACK -> RIGHT FORWARD / LEFT STOP");

    stopLeft();
    rightForward();
  }


  // ===============================
  // LEFT WHITE + RIGHT BLACK
  // LEFT = REVERSE
  // RIGHT = STOP
  // ===============================

  else if (!leftBlack && rightBlack) {

    Serial.println("WHITE + BLACK -> LEFT REVERSE / RIGHT STOP");

    leftReverse();
    stopRight();
  }


  // ===============================
  // LEFT BLACK + RIGHT WHITE
  // LEFT = STOP
  // RIGHT = REVERSE
  // ===============================

  else if (leftBlack && !rightBlack) {

    Serial.println("BLACK + WHITE -> LEFT STOP / RIGHT REVERSE");

    stopLeft();
    rightReverse();
  }


  // ===============================
  // BOTH WHITE
  // BOTH = REVERSE
  // ===============================

  else if (!leftBlack && !rightBlack) {

    Serial.println("WHITE + WHITE -> BOTH REVERSE");

    leftReverse();
    rightReverse();
  }

  delay(50);
}


// =================================
// LEFT MOTOR
// =================================

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


// =================================
// RIGHT MOTOR
// =================================

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