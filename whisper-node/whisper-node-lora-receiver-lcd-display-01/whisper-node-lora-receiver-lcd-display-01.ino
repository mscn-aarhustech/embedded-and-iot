#include <SPI.h>
#include <RH_RF95.h>
#include <DIYables_LCD_I2C.h>

/*

*/

// Pinout for Arduino Uno
#define RFM95_CS   10  // NSS (chip select)
#define RFM95_RST  7   // RESET
#define RFM95_INT  2   // DIO0, tied to INT0

// Radio Config
#define RF95_FREQ 433.0 // MUST MATCH TRANSMITTER
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// LCD display config
DIYables_LCD_I2C lcd(0x27, 20, 4);

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

  // Trade data rate for range: SF7 (default) is fast but short-range.
  // SF12 is ~5-10x the range of SF7 at the cost of a much slower data rate -
  // easily worth it for a payload this small. Comment out to keep default SF7.
  //rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);
  if (!rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096)) {
    Serial.println("setModemConfig failed");
    while (1);
  }
  
  Serial.println("Waiting for messages...");

  // LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // Add a null terminator to the end of the message
      buf[len] = '\0';
      
      // Serial
      Serial.print("Message: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.print("SNR: ");
      Serial.println(rf95.lastSNR(), DEC);
      Serial.println("--------------------------------");

      // LCD display
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MSG  : ");
      lcd.print((char*)buf);
      lcd.setCursor(0, 1);
      lcd.print("RSSI : ");
      lcd.print(rf95.lastRssi(), DEC);
      lcd.setCursor(0, 2);
      lcd.print("SNR  : ");
      lcd.print(rf95.lastSNR(), DEC);

    } else {
      Serial.println("Receive failed");
    }
  }
}