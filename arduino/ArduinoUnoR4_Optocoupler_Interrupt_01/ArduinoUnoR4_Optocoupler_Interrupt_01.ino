// Slot-type Optocoupler Module (LM393-based) - Interrupt version
// Counts pulses as objects pass through the slot, no delay() used.
//
// Wiring:
//   Module VCC -> Arduino 5V
//   Module GND -> Arduino GND
//   Module DO  -> Arduino D2 (must be pin 2 or 3 on Uno for hardware interrupts)

const byte DO_PIN = 2;          // INT0 on Uno
const unsigned long REPORT_INTERVAL_MS = 1000; // how often to print results

volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;
const unsigned long DEBOUNCE_US = 1000; // ignore edges closer than 1ms apart (adjust as needed)

unsigned long lastReportTime = 0;

void countPulse() {
  unsigned long now = micros();
  // simple debounce to avoid double-counting noisy edges
  if (now - lastPulseTime > DEBOUNCE_US) {
    pulseCount++;
    lastPulseTime = now;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DO_PIN, INPUT);

  // FALLING = triggers when slot goes from clear (HIGH) to blocked (LOW)
  attachInterrupt(digitalPinToInterrupt(DO_PIN), countPulse, FALLING);

  Serial.println("Interrupt-based slot optocoupler counter started.");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastReportTime >= REPORT_INTERVAL_MS) {
    lastReportTime = currentTime;

    // Safely copy the volatile counter
    noInterrupts();
    unsigned long count = pulseCount;
    pulseCount = 0;
    interrupts();

    // Pulses per second -> convert to RPM if each rotation gives 1 pulse
    float pulsesPerSecond = count / (REPORT_INTERVAL_MS / 1000.0);
    float rpm = pulsesPerSecond * 60.0;

    Serial.print("Pulses/sec: ");
    Serial.print(pulsesPerSecond);
    Serial.print("  |  RPM (if 1 pulse/rev): ");
    Serial.println(rpm);
  }

  // Rest of your program can run freely here, unblocked
}