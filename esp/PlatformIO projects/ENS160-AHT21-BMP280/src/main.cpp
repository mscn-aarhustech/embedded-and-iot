#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(21, 22); // SDA, SCL on ESP32 -- shared bus with AHT21/ENS160

  Serial.println(F("BMP280 test."));

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,
                   Adafruit_BMP280::SAMPLING_X2,  /* Temp. oversampling */
                   Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
                   Adafruit_BMP280::FILTER_X16,
                   Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  if (bmp.takeForcedMeasurement()) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1017.85)); // adjust to local sea-level pressure
    Serial.println(" m");

    Serial.println();
  } else {
    Serial.println("Forced measurement failed!");
  }
  delay(2000);
}