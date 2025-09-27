// NRF24L01 wireless Serial Transceiver Module
// Test code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

void setup() {
  Serial.begin(9600);
  
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Freeze
  }
  
  // Print radio details
  radio.printDetails();
}

void loop() {
  // Nothing to do here for this test
}