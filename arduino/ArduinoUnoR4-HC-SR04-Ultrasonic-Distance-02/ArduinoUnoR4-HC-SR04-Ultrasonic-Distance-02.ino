/*
  HC-SR04 Ultrasonic Distance Sensor Demo
  ----------------------------------------
  Wiring:
    VCC  -> Arduino 3.3V
    GND  -> Arduino GND
    TRIG -> Arduino Pin 9
    ECHO -> Arduino Pin 10
*/

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Clean LOW pulse before triggering
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // 10 microsecond trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the Echo pulse in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration > 0) {  
    // Calculate distance in cm (speed of sound = 0.0343 cm/microsecond)
    float distanceCm = (duration * 0.0343) / 2.0;

    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm ");
  } else {
    Serial.println("No echo received");
  }

  delay(500);
}
