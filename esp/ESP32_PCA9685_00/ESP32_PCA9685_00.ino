#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create a servo driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // Minimum pulse length for most servos
#define SERVOMAX  600 // Maximum pulse length for most servos
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test");
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ); // Set frequency to 50Hz
}

void loop() {
  // Sweep servo on channel 0
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
    delay(1);
  }
  delay(500);
  
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen);
    delay(1);
  }
  delay(500);
}   