const int xAxisPin = A1;
const int yAxisPin = A2;

int xAxisState = 0;
int yAxisState = 0;
char buffer[64];

void setup() {
  Serial.begin(9600);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
}

void loop() {
  xAxisState = analogRead(xAxisPin);
  yAxisState = analogRead(yAxisPin);

  sprintf(buffer, "xAxisState: %d, yAxisState: %d", xAxisState, yAxisState);
  Serial.println(buffer);
  delay(10);
}

