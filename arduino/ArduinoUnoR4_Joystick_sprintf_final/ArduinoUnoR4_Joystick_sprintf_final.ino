const int buttonPin = 2;
const int xAxisPin = A0;
const int yAxisPin = A1;

int buttonState = 0;
int xAxisState = 0;
int yAxisState = 0;
float xAxisNormalized = 0.0f;
float yAxisNormalized = 0.0f;
char buffer[64];

void setup() {
  Serial.begin(4800);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  analogReadResolution(12);
}

void loop() {
  buttonState = !digitalRead(buttonPin);
  xAxisState = analogRead(xAxisPin);
  yAxisState = analogRead(yAxisPin);

  xAxisNormalized = ((float)xAxisState / 2048.0f) - 1.0f;
  yAxisNormalized = -(((float)yAxisState / 2048.0f) - 1.0f);

  sprintf(buffer, "buttonState: %d, xAxisNormalized: %.4f, yAxisNormalized: %.4f", buttonState, xAxisNormalized, yAxisNormalized);
  Serial.println(buffer);
  delay(50);
}
