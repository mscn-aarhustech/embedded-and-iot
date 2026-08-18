/*
  ----------------------------------------
  Description:
  This demo measures the time in microseconds
  and distance in cm from an ultrasonic signal 
  is sent to its echo is registered.
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
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  // Reset
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send impulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;
  
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" us");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}   