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

uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
int RSSI = 0;
int SNR = 0;

unsigned long previousMillis = 0;
unsigned long lastMsgMillis = 0;
const long LCDinterval = 1000;

void setup() {

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  // LCD
  lcd.init();
  lcd.backlight();

  // Manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  lcd.setCursor(0, 0);
  if (!rf95.init()) {
    lcd.print("LoRa init failed");
    while (1);
  }
  lcd.print("LoRa init OK!");

  lcd.setCursor(0, 1);
  if (!rf95.setFrequency(RF95_FREQ)) {
    lcd.print("setFrequency failed");
    while (1);
  }
  lcd.print("Set Freq to: "); lcd.print(RF95_FREQ);

  // Trade data rate for range: SF7 (default) is fast but short-range.
  // SF12 is ~5-10x the range of SF7 at the cost of a much slower data rate -
  // easily worth it for a payload this small. Comment out to keep default SF7.
  //rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);
  lcd.setCursor(0, 2);
  if (!rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096)) {
    lcd.print("setModemConfig failed");
    while (1);
  }
  lcd.print("Waiting for messages");

  delay(4000);
  lcd.clear();
}

void loop() {
  
  unsigned long currentMillis = millis();

  // LoRa
  if (rf95.available()) {
    if (rf95.recv(buf, &len)) {
      // Add a null terminator to the end of the message
      buf[len] = '\0';
      RSSI = rf95.lastRssi();
      SNR = rf95.lastSNR();
      lastMsgMillis = currentMillis;
    } else {
    }
  }

  // Update LCD display once every second
  if (currentMillis - previousMillis >= LCDinterval) {
    // save the last time
    previousMillis = currentMillis;

    int s = (currentMillis - lastMsgMillis) / 1000;
    int m = s / 60;
    int h = m / 60;
    int d = h / 24;

    char msgbuffer[16];
    char rssibuffer[16];
    char snrbuffer[16];
    char timebuffer[16];

    snprintf(msgbuffer, sizeof(msgbuffer), "%s", (char*)buf);
    snprintf(rssibuffer, sizeof(rssibuffer), "%4d", RSSI);
    snprintf(snrbuffer, sizeof(snrbuffer), "%2d", SNR);
    snprintf(timebuffer, sizeof(timebuffer), "%03d:%02d:%02d:%02d", d % 1000, h % 24, m % 60, s % 60);

    lcd.setCursor(0, 0); lcd.print("MSG  : "); lcd.print(msgbuffer);
    lcd.setCursor(0, 1); lcd.print("RSSI : "); lcd.print(rssibuffer);
    lcd.setCursor(0, 2); lcd.print("SNR  : "); lcd.print(snrbuffer);
    lcd.setCursor(0, 3); lcd.print("LAST : "); lcd.print(timebuffer);
  }
}