#include <Arduino.h>

// Pin Definitions
int motor_lA = 2;    // Left motor forward
int motor_lB = 3;    // Left motor reverse
int motor_enableA = 10;

int motor_rA = 4;    // Right motor forward
int motor_rB = 5;    // Right motor reverse
int motor_enableB = 11;

int trigger_front = A0;
int echo_front = A1;

int trigger_left = A2;
int echo_left = A3;

int trigger_right = A4;
int echo_right = A5;

void setup() {
  // Motor pins setup
  pinMode(motor_lA, OUTPUT);
  pinMode(motor_lB, OUTPUT);
  pinMode(motor_enableA, OUTPUT);
  
  pinMode(motor_rA, OUTPUT);
  pinMode(motor_rB, OUTPUT);
  pinMode(motor_enableB, OUTPUT);
  
  // Ultrasonic sensor pins setup
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  
  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);
  
  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);
  
  // Set motor speeds
  analogWrite(motor_enableA, 170);
  analogWrite(motor_enableB, 178);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure distances
  long duration_front, distance_front, 
       duration_left, distance_left, 
       duration_right, distance_right;
  
  // Measure front distance
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  duration_front = pulseIn(echo_front, HIGH);
  distance_front = duration_front * 0.034 / 2;
  
  // Measure left distance
  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  duration_left = pulseIn(echo_left, HIGH);
  distance_left = duration_left * 0.034 / 2;
  
  // Measure right distance
  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  duration_right = pulseIn(echo_right, HIGH);
  distance_right = duration_right * 0.034 / 2;
  
  // Print distances for debugging
  Serial.print("Front = ");
  Serial.print(distance_front);
  Serial.print(" cm, Left = ");
  Serial.print(distance_left);
  Serial.print(" cm, Right = ");
  Serial.println(distance_right);
  
  // Decision-making logic
  if (distance_front > 30) {
    // Path ahead is clear, move forward
    forward();
    delay(100);
/*     
    // Wall following logic
    if (distance_left > 20) {
      // Too far from left wall, turn left to get closer
      left();
      delay(50);
      forward();
    } else if (distance_left < 10) {
      // Too close to left wall, turn right to move away
      right();
      delay(50);
      forward();
    } */
  } else {
    // Obstacle in front, decide which way to turn
    Stop();
    delay(500);
    
    if (distance_right > 20) {
      // If right side is clear, turn right
      right();
      delay(150);
    } else if (distance_left > 20) {
      // If left side is clear, turn left
      left();
      delay(150);
    } else {
      // Completely blocked, perform a 180-degree turn
      right();
      delay(400);
    }
  }
  
  // Short delay to prevent rapid sensor readings
  delay(50);
}

// Motor control functions
void forward() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(200);
}

void right() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(200);  // Adjusted turn duration
}

void left() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(200);  // Adjusted turn duration
}

void Stop() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  delay(200);
}
