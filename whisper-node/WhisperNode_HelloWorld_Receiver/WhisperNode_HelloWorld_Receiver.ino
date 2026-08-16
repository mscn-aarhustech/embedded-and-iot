/*
  WhisperNode_HelloWorld_Receiver.ino
  ------------------------------------
  "Hello, World!" LoRa receiver for the Wisen/Talk2 Whisper Node LoRa
  (ATmega328P + RFM95/SX1276), using the RadioLib library.

  Library:  RadioLib by jgromes
            Install via Arduino IDE: Sketch > Include Library > Manage Libraries > search "RadioLib"
            https://github.com/jgromes/RadioLib

  Wiring (matches the Whisper Node LoRa's onboard RFM95, per RadioHead docs):
    NSS  (chip select) -> D10
    DIO0 (IRQ)          -> D2
    RESET                -> not broken out on most Whisper Node boards -> RADIOLIB_NC

  Flash this sketch to the SECOND of your two Whisper Node modules.
  Flash the companion "Transmitter" sketch to the other one.
*/

#include <RadioLib.h>

// NSS = 10, DIO0(IRQ) = 2, RESET = not connected, DIO1/GPIO = not connected
SX1276 radio = new Module(10, 2, RADIOLIB_NC, RADIOLIB_NC);

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); }

  Serial.print(F("[SX1276] Initializing ... "));

  // Must match the transmitter's frequency exactly (433.0, 868.0, or 915.0 MHz)
  int state = radio.begin(915.0);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); } // halt
  }

  // Must match the transmitter's radio settings
  radio.setBandwidth(125.0);
  radio.setSpreadingFactor(7);
  radio.setCodingRate(5);

  Serial.println(F("Listening for LoRa packets..."));
}

void loop() {
  String receivedData;
  int state = radio.receive(receivedData);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Received packet!"));
    Serial.print(F("  Data:\t\t"));
    Serial.println(receivedData);
    Serial.print(F("  RSSI:\t\t"));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));
    Serial.print(F("  SNR:\t\t"));
    Serial.print(radio.getSNR());
    Serial.println(F(" dB"));
  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
    // no packet received within timeout window, keep listening
  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
    Serial.println(F("CRC error!"));
  } else {
    Serial.print(F("Receive failed, code "));
    Serial.println(state);
  }
}
