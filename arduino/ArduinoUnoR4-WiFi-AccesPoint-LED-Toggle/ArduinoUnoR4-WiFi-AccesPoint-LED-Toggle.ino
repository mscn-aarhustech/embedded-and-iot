/*
  WiFi Web Server LED Toggle (Access Point mode)

  Serves a single-page HTML/JS UI with a toggle button.
  The Arduino tracks LED state server-side; the browser calls
  /toggle to flip it and /status to read the current state.

  http://yourAddress/       -> HTML page with toggle button
  http://yourAddress/toggle -> flips the LED, returns JSON state
  http://yourAddress/status -> returns JSON state without changing it
*/

#include "WiFiS3.h"
#include "arduino_secrets.h"
#include "html.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

bool ledState = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Access Point Web Server");

  pinMode(led, OUTPUT);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  WiFi.config(IPAddress(192, 48, 56, 2));

  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }

  delay(10000);

  server.begin();
  printWiFiStatus();
}

void loop() {
  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    String requestLine = "";   // NEW: holds just the first line, e.g. "GET /toggle HTTP/1.1"
    bool gotRequestLine = false; // NEW: tracks whether we've captured it yet

    while (client.connected()) {
      delayMicroseconds(10);
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {

          // NEW: the first line we complete IS the request line — save it once
          if (!gotRequestLine) {
            requestLine = currentLine;
            gotRequestLine = true;
          }

          // Blank line = end of headers = time to respond
          if (currentLine.length() == 0) {

            // CHANGED: route decisions now check requestLine, not currentLine,
            // and use startsWith with a trailing space so "/status" doesn't
            // also match a hypothetical "/statusfoo"
            if (requestLine.startsWith("GET /toggle ")) {
              ledState = !ledState;
              digitalWrite(led, ledState ? HIGH : LOW);
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:application/json");
              client.println();
              client.print("{\"state\":");
              client.print(ledState ? "1" : "0");
              client.print("}");
            } else if (requestLine.startsWith("GET /status ")) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:application/json");
              client.println();
              client.print("{\"state\":");
              client.print(ledState ? "1" : "0");
              client.print("}");
            } else {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.print(htmlPage);
            }
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}