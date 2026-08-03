const int buttonPin = 2;
const int xAxisPin = A0;
const int yAxisPin = A1;

int buttonState = 0;
int xAxisState = 0;
int yAxisState = 0;
char buffer[64];

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  xAxisState = analogRead(xAxisPin);
  yAxisState = analogRead(yAxisPin);
  
  // if(buttonState == LOW) {
  //   Serial.println("pressed!");
  // } else {
  //   Serial.println("not pressed!");
  // }

  sprintf(buffer, "buttonState: %d, xAxisState: %.2f, xAxisState: %.2f", buttonState, xAxisState, yAxisState);
  Serial.println(buffer);
  delay(10);
}
