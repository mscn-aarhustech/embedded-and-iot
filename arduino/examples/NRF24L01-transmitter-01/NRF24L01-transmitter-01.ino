// NRF24L01 wireless Serial Transceiver Module
// Transmitter code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Initialize the NRF24L01 radio object with CE and CSN pins
RF24 radio(9, 10); // CE, CSN

// Create a 'pipe' address. This must be the same for both the transmitter and receiver.
const byte address[6] = "00001";

void setup() {
  radio.begin(); // Start the radio
  
  // Set the address
  radio.openWritingPipe(address);
  
  // Set the power amplifier level. MAX is for best range.
  radio.setPALevel(RF24_PA_MAX);
  
  // Stop listening, so we can transmit
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  
  // Send the message
  radio.write(&text, sizeof(text));
  
  // Wait a second before sending the next one
  delay(1000);
}