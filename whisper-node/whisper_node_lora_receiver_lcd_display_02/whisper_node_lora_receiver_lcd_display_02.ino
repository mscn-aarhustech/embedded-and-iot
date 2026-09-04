/*
 * This Arduino Nano ESP32 code was developed by newbiely.com
 *
 * This Arduino Nano ESP32 code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/arduino-nano-esp32/arduino-nano-esp32-servo-motor
 */

#include <ESP32Servo.h>

#define SERVO_PIN 18 // The Arduino Nano ESP32 pin connected to servo motor

Servo servoMotor;

void setup() {
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
}

void loop() {
  // rotates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }

  // rotates from 180 degrees to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}
