// Slot-type Optocoupler Module (LM393-based) test sketch
// Wiring:
//   Module VCC -> Arduino 5V
//   Module GND -> Arduino GND
//   Module DO  -> Arduino D2 (digital output)
//   (optional) Module AO -> Arduino A0 (analog output, if broken out)

const int DO_PIN = 2;
const int AO_PIN = A0;   // remove/ignore if your board has no AO pin
const int LED_PIN = 13;  // onboard LED mirrors the sensor state

void setup() {
  Serial.begin(9600);
  pinMode(DO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Slot optocoupler test started.");
  Serial.println("Insert/remove an object in the slot to see the state change.");
}

void loop() {
  int state = digitalRead(DO_PIN);

  // Module logic: LOW = slot blocked (object detected), HIGH = slot clear
  if (state == HIGH) {
    Serial.println("Slot BLOCKED (object detected)");
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("Slot clear");
    digitalWrite(LED_PIN, LOW);
  }

  // Optional: read the raw analog signal too, if AO is wired
  int analogVal = analogRead(AO_PIN);
  Serial.print("Analog reading: ");
  Serial.println(analogVal);

  delay(50);
}