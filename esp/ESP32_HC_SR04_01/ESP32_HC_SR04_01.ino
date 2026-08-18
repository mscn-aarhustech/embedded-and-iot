/*
  ----------------------------------------
  Description:
  This demo measures the time in microseconds
  from an ultrasonic signal is sent to its
  echo is registered.
  ----------------------------------------
  Parts:
  HC-SR04 Ultrasonic Distance Sensor
  ESP32 38-Pin Development Board
  ----------------------------------------
  Wiring:
    HC-SR04 -> ESP32
    VCC     -> 3.3V
    GND     -> GND
    TRIG    -> GPIO Pin 5
    ECHO    -> GPIO Pin 18
  ----------------------------------------
*/

#include <Arduino.h>

const int trigPin = 5;
const int echoPin = 18;
long duration;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  // Reset trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 us impulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" us");

  delay(500);
}   