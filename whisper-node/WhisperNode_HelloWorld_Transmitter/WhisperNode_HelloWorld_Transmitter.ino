/*
  WhisperNode_HelloWorld_Transmitter.ino
  ---------------------------------------
  "Hello, World!" LoRa transmitter for the Wisen/Talk2 Whisper Node LoRa
  (ATmega328P + RFM95/SX1276), using the RadioLib library.

  Library:  RadioLib by jgromes
            Install via Arduino IDE: Sketch > Include Library > Manage Libraries > search "RadioLib"
            https://github.com/jgromes/RadioLib

  Wiring (matches the Whisper Node LoRa's onboard RFM95, per RadioHead docs):
    NSS  (chip select) -> D10
    DIO0 (IRQ)          -> D2
    RESET                -> not broken out on most Whisper Node boards -> RADIOLIB_NC

  Flash this sketch to ONE of your two Whisper Node modules.
  Flash the companion "Receiver" sketch to the other one.
*/

// Strip out unused protocol layers to fit the ATmega328P's 32KB flash.
// Must be defined BEFORE including RadioLib.h, and must have a value (1),
// since RadioLib's headers use "#if !RADIOLIB_EXCLUDE_X" (not "#ifdef").
#define RADIOLIB_EXCLUDE_AFSK 1
#define RADIOLIB_EXCLUDE_AX25 1
#define RADIOLIB_EXCLUDE_BELL 1
#define RADIOLIB_EXCLUDE_HELLSCHREIBER 1
#define RADIOLIB_EXCLUDE_MORSE 1
#define RADIOLIB_EXCLUDE_RTTY 1
#define RADIOLIB_EXCLUDE_SSTV 1
#define RADIOLIB_EXCLUDE_PAGER 1
#define RADIOLIB_EXCLUDE_FSK4 1
#define RADIOLIB_EXCLUDE_APRS 1
#define RADIOLIB_EXCLUDE_LORAWAN 1

#include <RadioLib.h>

// NSS = 10, DIO0(IRQ) = 2, RESET = not connected, DIO1/GPIO = not connected
SX1276 radio = new Module(10, 2, RADIOLIB_NC, RADIOLIB_NC);

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); }

  Serial.print(F("[SX1276] Initializing ... "));

  // IMPORTANT: set this to match YOUR board's hardware frequency variant
  // (433.0, 868.0, or 915.0 MHz). Using the wrong frequency for your
  // region/hardware is both illegal and won't talk to the other node.
  int state = radio.begin(433.0);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); } // halt
  }

  // Reasonable defaults (adjust to your license-free band's rules if needed)
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