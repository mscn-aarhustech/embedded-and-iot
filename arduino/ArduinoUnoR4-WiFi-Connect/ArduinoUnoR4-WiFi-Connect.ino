#include <WiFiS3.h>

char ssid[] = "enter-ssid-here";
char pass[] = "enter-password-here";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(100);
  }
}

void loop() {
}
