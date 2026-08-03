#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

byte frame[8][12];

void setup() {
  matrix.begin();
  frame[0][0] = 1;
  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
}



