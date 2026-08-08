#include <WiFiS3.h>

const char* ssid     = "ASUS_B8_IoT";
const char* password = "Q_72-asoPLN~8";

WiFiServer server(80);
bool ledState = false;

// ---- index.html ----
const char PAGE_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <link rel="stylesheet" href="/style.css">
</head>
<body>
  <h1>Uno R4 WiFi</h1>
  <p>LED is <span id="state">...</span></p>
  <button onclick="toggleLed()">Toggle LED</button>
  <script src="/script.js"></script>
</body>
</html>
)=====";

// ---- style.css ----
const char PAGE_CSS[] PROGMEM = R"=====(
body {
  font-family: sans-serif;
  text-align: center;
  margin-top: 60px;
  background: #222;
  color: #eee;
}

button {
  font-size: 1.2em;
  padding: 10px 20px;
  border-radius: 8px;
  border: none;
  background: #38bdf8;
  cursor: pointer;
}
)=====";

// ---- script.js ----
const char PAGE_JS[] PROGMEM = R"=====(
async function toggleLed() {
  const res = await fetch('/toggle');
  const on = await res.text();
  document.getElementById('state').textContent = on === "1" ? "ON" : "OFF";
}

window.onload = toggleLed;
)=====";

void sendFile(WiFiClient& client, const char* contentType, const char* data) {
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");
  client.println();
  client.println((const __FlashStringHelper*)data);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    Serial.println("Getting IP address...");
    delay(200);
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("GET / ") >= 0) {
    sendFile(client, "text/html", PAGE_HTML);
  } else if (request.indexOf("GET /style.css") >= 0) {
    sendFile(client, "text/css", PAGE_CSS);
  } else if (request.indexOf("GET /script.js") >= 0) {
    sendFile(client, "application/javascript", PAGE_JS);
  } else if (request.indexOf("GET /toggle") >= 0) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println(ledState ? "1" : "0");
  } else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Connection: close");
    client.println();
  }

  delay(1);
  client.stop();
}
