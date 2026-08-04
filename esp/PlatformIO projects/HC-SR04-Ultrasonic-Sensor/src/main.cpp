/*
  HC-SR04 Ultrasonic Distance Sensor Demo
  ESP32 38-Pin Development Board
  ----------------------------------------
  Wiring:
    VCC  -> ESP32 3.3V
    GND  -> ESP32 GND
    TRIG -> ESP32 Pin 5
    ECHO -> ESP32 Pin 18
*/

#include <Arduino.h>

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
  // Set trigger pin to low before triggering
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // 10 microseconds trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the Echo pulse in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration > 0) {  
    // Calculate distance in cm 
    // (speed of sound = 343 m/sec = 0.0343 cm/microsecond)
    float distanceCm = (duration * 0.0343) / 2.0;

    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm ");
  } else {
    Serial.println("No echo received");
  }

  delay(500);
}