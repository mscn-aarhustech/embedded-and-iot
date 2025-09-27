#include <SPI.h>
#include <RH_RF95.h>

// == Pinout for Arduino Uno (Adafruit Tutorial) ==
#define RFM95_CS   4
#define RFM95_RST  2
#define RFM95_INT  3

// == Radio Config ==
#define RF95_FREQ 433.0 // MUST MATCH TRANSMITTER

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  while (!Serial);

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
  
  Serial.println("Waiting for messages...");
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // Add a null terminator to the end of the message
      buf[len] = '\0';
      
      Serial.print("Got message: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.println("--------------------------------");
    } else {
      Serial.println("Receive failed");
    }
  }
}