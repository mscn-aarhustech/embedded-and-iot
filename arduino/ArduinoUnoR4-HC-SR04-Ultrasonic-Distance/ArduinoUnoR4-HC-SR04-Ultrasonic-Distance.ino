// /*
//   HC-SR04 Ultrasonic Distance Sensor Demo
//   ----------------------------------------
//   Wiring:
//     VCC  -> Arduino 5V
//     GND  -> Arduino GND
//     TRIG -> Arduino Pin 9
//     ECHO -> Arduino Pin 10
// */

// const int TRIG_PIN = 9;
// const int ECHO_PIN = 10;

// void setup() {
//   Serial.begin(9600);
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);
//   digitalWrite(TRIG_PIN, LOW);
//   delay(50);
// }

// void loop() {
//   // Clean LOW pulse before triggering
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);

//   // 10us trigger pulse
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   // Measure echo pulse duration (timeout ~30ms = ~5m range)
//   long duration = pulseIn(ECHO_PIN, HIGH, 30000);

//   if (duration == 0) {
//     Serial.println("No echo received (out of range or no object)");
//   } else {
//     float distanceCm = (duration * 0.0343) / 2.0; // round trip
//     float distanceIn = distanceCm / 2.54;

//     Serial.print("Distance: ");
//     Serial.print(distanceCm);
//     Serial.print(" cm (");
//     Serial.print(distanceIn);
//     Serial.println(" in)");
//   }

//   delay(500);
// }

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
