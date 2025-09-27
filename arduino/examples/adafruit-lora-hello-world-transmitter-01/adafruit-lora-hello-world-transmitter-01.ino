#include <SPI.h>
#include <RH_RF95.h>

// == Pinout for Arduino Uno (Adafruit Tutorial) ==
#define RFM95_CS   4
#define RFM95_RST  2
#define RFM95_INT  3

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
}

void loop() {
  delay(1000); // Wait 1 second
  
  char radiopacket[20];
  sprintf(radiopacket, "Hello World #%d", packetnum++);
  
  Serial.print("Sending: "); Serial.println(radiopacket);
  
  rf95.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf95.waitPacketSent();
}