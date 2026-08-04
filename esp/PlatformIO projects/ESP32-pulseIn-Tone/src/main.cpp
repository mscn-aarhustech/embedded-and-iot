/*
  Wiring:
  ESP32 pin 4 (TONE_PIN) -> ESP32 pin 18 (INPUT_PIN)
*/

#include <Arduino.h>

const int TONE_PIN = 4;
const int INPUT_PIN = 18;

// Frequency in Herz
const int FREQ = 100;
// Period in seconds
const float PERIOD = 1.0 / FREQ;
// Period in microseconds
const float PERIOD_US = PERIOD * 1e6;
// Fraction of period pin should be HIGH
const float DUTY_CYCLE = 0.5;
// Microseconds pin should be HIGH
const int EXPECTED_PERIOD_US = PERIOD_US * DUTY_CYCLE;

void setup() {
  Serial.begin(115200);
  pinMode(INPUT_PIN, INPUT);
  tone(TONE_PIN, FREQ);
}

void loop() {
  long duration_us = pulseIn(INPUT_PIN, HIGH);

  Serial.print("Measured: ");
  Serial.print(duration_us);
  Serial.print(" us | Expected: ");
  Serial.print(EXPECTED_PERIOD_US);
  Serial.println(" us");

  delay(500);
}