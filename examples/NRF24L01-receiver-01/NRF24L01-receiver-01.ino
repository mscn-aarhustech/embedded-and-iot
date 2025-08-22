// NRF24L01 wireless Serial Transceiver Module
// Receiver code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Initialize the NRF24L01 radio object with the same CE and CSN pins
RF24 radio(9, 10); // CE, CSN

// Use the exact same 'pipe' address as the transmitter
const byte address[6] = "00001";

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  
  radio.begin(); // Start the radio
  
  // Set the address
  radio.openReadingPipe(0, address); // Use pipe 0 for reading
  
  // Set the power amplifier level
  radio.setPALevel(RF24_PA_MAX);
  
  // Start listening for incoming data
  radio.startListening();
  
  Serial.println("Receiver is ready and listening...");
}

void loop() {
  // Check if there is any data available to be read
  if (radio.available()) {
    char text[32] = ""; // Create a buffer to hold the received data
    
    // Read the data into the buffer
    radio.read(&text, sizeof(text));
    
    // Print the received message to the Serial Monitor
    Serial.println(text);
  }
}