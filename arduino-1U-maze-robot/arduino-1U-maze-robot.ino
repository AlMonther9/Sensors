// Pin definitions
#define ENA 5
#define IN1 4
#define IN2 3
#define IN3 9
#define IN4 10
#define ENB 11

#define TRIG_PIN1 A0
#define ECHO_PIN1 A1

#define DIST_THRESHOLD 20 // Distance threshold in cm

// Function to calculate distance
long calculateDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert duration to cm
}

// Motor control functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void rotate180() {
  // Rotate the car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500); // Adjust delay for 180° rotation
  stopMotors();
}

void setup() {
  // Initialize pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);

  // Start the motors
  analogWrite(ENA, 150); // Set speed for Motor A
  analogWrite(ENB, 150); // Set speed for Motor B
}

void loop() {
  // Measure distance
  long distance = calculateDistance(TRIG_PIN1, ECHO_PIN1);

  if (distance < DIST_THRESHOLD) {
    stopMotors();
    delay(500); // Wait before rotating
    rotate180();
    delay(500); // Wait before moving forward again
  } else {
    moveForward();
  }

  delay(100); // Short delay for stability
}
