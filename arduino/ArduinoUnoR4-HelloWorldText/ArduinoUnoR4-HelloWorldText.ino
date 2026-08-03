#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();
}

void loop() {
  matrix.beginDraw();
  matrix.textScrollSpeed(50);
  const char text[] = "Hi!";
  //matrix.textFont(Font_5x7);
  matrix.textFont(Font_4x6);
  matrix.beginText(1, 2, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(NO_SCROLL);
  matrix.endDraw();
}

