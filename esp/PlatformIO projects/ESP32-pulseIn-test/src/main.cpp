#include <Arduino.h>

const int OUT_PIN = 4;   // held HIGH continuously — leave one end of a wire here
const int IN_PIN  = 18;  // student touches the other end of the wire to here

void setup() {
  Serial.begin(115200);
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, HIGH);   // always on
  pinMode(IN_PIN, INPUT_PULLDOWN); // reads LOW when nothing is touching it
}

void loop() {
  Serial.println("Touch the wire to IN_PIN, then let go...");
  long duration = pulseIn(IN_PIN, HIGH, 10000000); 
  Serial.print("Contact duration (microseconds): ");
  Serial.println(duration/1000000.0, 6); // convert to seconds and print with 6 decimal places
  delay(100);
}