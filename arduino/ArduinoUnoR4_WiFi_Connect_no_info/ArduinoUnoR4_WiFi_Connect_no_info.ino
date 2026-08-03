#include <WiFiS3.h>

char ssid[] = "ASUS_B8_IoT";
char pass[] = "Q_72-asoPLN~8";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(1000);
    Serial.println("Getting IP address...");
  }

  Serial.print("Connected!");
}

void loop() {
}
