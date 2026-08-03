#include <WiFiS3.h>
#include <ArduinoJson.h>

char ssid[] = "ASUS_B8_IoT";
char pass[] = "Q_72-asoPLN~8";
char server[] = "api.open-notify.org";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(1000);
  }
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    Serial.println("Getting IP address...");
    delay(200);
  }

  Serial.println("Connected!");

  if (client.connect(server, 80)) {
    Serial.println("Server connected, sending request...");
    client.println("GET /iss-now.json HTTP/1.1");
    client.println("Host: api.open-notify.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection to server FAILED");
  }
}

void loop() {
  if (client.available()) {
    //client.find("\r\n\r\n");

    //StaticJsonDocument<256> doc;
    //deserializeJson(doc, client);
    //Serial.println(doc.as<String>());
    Serial.println(client.readString());
    // Serial.print("ISS latitude: ");
    // Serial.println(doc["iss_position"]["latitude"].as<String>());
    // Serial.print("ISS longitude: ");
    // Serial.println(doc["iss_position"]["longitude"].as<String>());

    while (true);
  }
}