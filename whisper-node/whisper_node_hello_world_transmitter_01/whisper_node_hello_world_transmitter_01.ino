#include <SPI.h>
#include <RH_RF95.h>

// In Arduino IDE, select Board: Arduino Nano, Processor: Atmega328P

// == Pinout for wisen Talk2 Whisper Node ==
#define RFM95_CS   10
#define RFM95_RST  7
#define RFM95_INT  2

// == Radio Config ==
#define RF95_FREQ 433.0 // Change to 868.0 or 915.0 depending on your module

RH_RF95 rf95(RFM95_CS, RFM95_INT);
int16_t packetnum = 0;

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open

  // Manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  rf95.setTxPower(23, false);

  // Trade data rate for range: SF7 (default) is fast but short-range.
  // SF12 is ~5-10x the range of SF7 at the cost of a much slower data rate -
  // easily worth it for a payload this small. Comment out to keep default SF7.
  //rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);
  rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096);
}

void loop() {
  delay(5000); // Wait 5 seconds
  
  char radiopacket[16];
  sprintf(radiopacket, "%d", packetnum++);
  
  Serial.print("Sending: "); Serial.println(radiopacket);
  
  rf95.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf95.waitPacketSent();
}