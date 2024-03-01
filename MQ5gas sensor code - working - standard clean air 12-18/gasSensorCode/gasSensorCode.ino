const int gasSensorPin = A0; // Analog pin connected to the sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read the analog sensor value
  int sensorValue = analogRead(gasSensorPin);

  // Print the sensor value to the serial monitor
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  // Wait for a short delay
  delay(1000);
}
