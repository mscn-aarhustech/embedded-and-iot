const int xAxisPin = A1;

int xAxisState = 0;
char buffer[64];

void setup() {
  Serial.begin(4800);
  pinMode(xAxisPin, INPUT);
}

void loop() {
  xAxisState = analogRead(xAxisPin);

  sprintf(buffer, "xAxisState: %d", xAxisState);
  Serial.println(buffer);
  delay(50);
}

