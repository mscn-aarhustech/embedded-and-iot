const int buttonPin = 2;

const int bufferSize = 50;
unsigned long timestamps[bufferSize];
int states[bufferSize];
int eventCount = 0;

int lastState = HIGH;
unsigned long lastChangeMicros = 0;
const unsigned long quietPeriod = 50000; // 50ms of no change = "settled"

bool capturing = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Ready. Press the joystick button...");
}

void loop() {
  int reading = digitalRead(buttonPin);
  unsigned long now = micros();

  // Detect a raw transition
  if (reading != lastState) {
    lastState = reading;
    lastChangeMicros = now;
    capturing = true;

    if (eventCount < bufferSize) {
      timestamps[eventCount] = now;
      states[eventCount] = reading;
      eventCount++;
    }
  }

  // Once things go quiet for quietPeriod, dump the buffer
  if (capturing && (now - lastChangeMicros > quietPeriod)) {
    Serial.print("Captured ");
    Serial.print(eventCount);
    Serial.println(" transitions:");

    for (int i = 0; i < eventCount; i++) {
      unsigned long delta = (i == 0) ? 0 : (timestamps[i] - timestamps[i - 1]);
      Serial.print("  [");
      Serial.print(i);
      Serial.print("] t=");
      Serial.print(timestamps[i]);
      Serial.print("us  state=");
      Serial.print(states[i] == LOW ? "PRESSED" : "RELEASED");
      Serial.print("  (+");
      Serial.print(delta);
      Serial.println("us since last)");
    }

    Serial.println("---");

    // Reset for next press
    eventCount = 0;
    capturing = false;
  }
}