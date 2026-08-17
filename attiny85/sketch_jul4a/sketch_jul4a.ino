#include <SoftwareSerial.h>

#define TX_PIN 3
#define RX_PIN 4

SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  mySerial.begin(9600);
}

int n = 0;

void loop() {
  mySerial.println("Hello, world!");
  mySerial.println(String(n));
  n += 1;
  delay(1000);
}