#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Default I2C address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Typical pulse range for a 9g SG90-style servo, in "ticks" out of 4096
// at 50 Hz. Adjust if your servo doesn't hit full range or grinds at the ends.
#define SERVOMIN  80   // ~0.5ms pulse -> 0 degrees
#define SERVOMAX  620   // ~2.5ms pulse -> 180 degrees
#define SERVO_CHANNEL 0

int angleToTicks(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setup() {
  Serial.begin(115200);
  Serial.println("PCA9685 servo test starting...");

  Wire.begin(); // default SDA=21, SCL=22 on most ESP32 boards
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz

  delay(10);
}

void loop() {
  // Sweep 0 -> 180
  for (int angle = 0; angle <= 180; angle += 1) {
    pwm.setPWM(SERVO_CHANNEL, 0, angleToTicks(angle));
    delay(5);
  }

  delay(500);

  // Sweep 180 -> 0
  for (int angle = 180; angle >= 0; angle -= 1) {
    pwm.setPWM(SERVO_CHANNEL, 0, angleToTicks(angle));
    delay(5);
  }

  delay(500);
}