/*
  HC-SR04 Ultrasonic Distance Sensor Demo
  ESP32 38-Pin Development Board
  ----------------------------------------
  Wiring:
    HC-SR04 -> ESP32
    VCC     -> 3.3V
    GND     -> GND
    TRIG    -> GPIO Pin 5
    ECHO    -> GPIO Pin 18
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

  // Measure echo pulse delay in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" us ");

  delay(500);
}

