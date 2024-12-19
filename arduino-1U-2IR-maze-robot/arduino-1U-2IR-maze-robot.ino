// Ultrasonic Sensor Pins
#define TRIG_PIN A0  // Ultrasonic trigger pin
#define ECHO_PIN A1  // Ultrasonic echo pin

// IR Sensor Pins
#define IR_RIGHT 7   // Right IR sensor pin
#define IR_LEFT 8    // Left IR sensor pin

// Motor Control Pins
#define ENA 10  // Right motor enable pin
#define ENB 11  // Left motor enable pin
#define IN1 2   // Right motor direction pin 1
#define IN2 3   // Right motor direction pin 2
#define IN3 4   // Left motor direction pin 1
#define IN4 5   // Left motor direction pin 2

// Constants
#define MAX_DISTANCE 100 // Maximum distance in cm
#define TURN_DISTANCE 15 // Distance to an obstacle in cm

void setup() {
  // Setup motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Setup sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);

  // Start Serial Monitor
  Serial.begin(9600);
}

void loop() {
  int frontDistance = getUltrasonicDistance();
  bool rightDetected = digitalRead(IR_RIGHT) == HIGH;
  bool leftDetected = digitalRead(IR_LEFT) == HIGH;

  Serial.print("Front Distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm\tRight IR: ");
  Serial.print(rightDetected);
  Serial.print("\tLeft IR: ");
  Serial.println(leftDetected);

  // Default forward movement
  if (frontDistance > TURN_DISTANCE) {
    moveForward();
  } else {
    stopMotors();
    delay(500);

    if (!rightDetected) {
      turnRight();
    } else if (!leftDetected) {
      turnLeft();
    }/*  else {
      turnRight(); // Default to turning right
    } */
  }

  delay(100); // Loop delay for stability
}

// Ultrasonic Distance Measurement
int getUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Convert to cm
  return distance > MAX_DISTANCE ? MAX_DISTANCE : distance;
}

// Motor Control Functions
void moveForward() {
  analogWrite(ENA, 150); // Moderate speed
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300); // Adjust delay for turn angle
}

void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300); // Adjust delay for turn angle
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
