#include <RadioLib.h>

// NSS = 10, DIO0(IRQ) = 2, RESET = not connected, DIO1/GPIO = not connected
SX1276 radio = new Module(10, 2, RADIOLIB_NC, RADIOLIB_NC);

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); }

  Serial.print(F("[SX1276] Initializing ... "));

  // Set to match YOUR board's hardware frequency variant (433.0, 868.0, or 915.0 MHz)
  int state = radio.begin(433.0);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  radio.setBandwidth(125.0);
  radio.setSpreadingFactor(7);
  radio.setCodingRate(5);
  radio.setOutputPower(13); // dBm
}

void loop() {
  Serial.print(F("[SX1276] Sending 'Hello, World!' ... "));

  int state = radio.transmit("Hello, World!");

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
    Serial.print(F("[SX1276] Data rate:\t"));
    // Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));
  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    Serial.println(F("too long!"));
  } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
    Serial.println(F("timeout!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
  }

  delay(2000);
}