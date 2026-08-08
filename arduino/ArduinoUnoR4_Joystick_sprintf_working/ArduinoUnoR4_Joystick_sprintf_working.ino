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
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  analogReadResolution(12);
}

void loop() {
  buttonState = !digitalRead(buttonPin);
  xAxisState = analogRead(xAxisPin);
  yAxisState = analogRead(yAxisPin);

  // map [0, 4095] -> [-1, 1]
  xAxisNormalized = (xAxisState / (float)4095) * 2.0f - 1.0f;
  yAxisNormalized = -((yAxisState / (float)4095) * 2.0f - 1.0f);

  sprintf(buffer, "b: %d, x: %.3f, y: %.3f", buttonState, xAxisNormalized, yAxisNormalized);
  Serial.println(buffer);
  // 100 fps
  delay(10);
}
