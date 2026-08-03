#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();
}

void loop() {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.line(0, 5, 5, 7);
  matrix.circle(8, 3, 6);
  matrix.rect(0, 0, 4, 4);
  matrix.point(8, 3);
  matrix.endDraw();
}

