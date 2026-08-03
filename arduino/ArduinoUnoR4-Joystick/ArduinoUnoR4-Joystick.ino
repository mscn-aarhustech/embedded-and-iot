const int buttonPin = 2;
const int xAxisPin = A0;
const int yAxisPin = A1;

int buttonState = 0;
int xAxisState = 0;
int yAxisState = 0;
char buffer[64];

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
}

void loop() {
  buttonState = !digitalRead(buttonPin);
  xAxisState = analogRead(xAxisPin);
  yAxisState = analogRead(yAxisPin);

  sprintf(buffer, "buttonState: %d, xAxisState: %d, yAxisState: %d", buttonState, xAxisState, yAxisState);
  Serial.println(buffer);
  delay(10);
}
