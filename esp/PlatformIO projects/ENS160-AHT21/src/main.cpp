/*!
 * ENS160 + AHT21 combined air quality & climate sketch
 *
 * AHT21: Adafruit_AHTX0 library (temperature + humidity)
 * ENS160: DFRobot_ENS160 library (AQI, TVOC, eCO2)
 *
 * The AHT21 reading is fed into the ENS160 each loop via setTempAndHum()
 * so the gas-sensing algorithm compensates for real ambient conditions
 * instead of using a fixed default -- this significantly improves
 * TVOC/eCO2 accuracy.
 */
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <DFRobot_ENS160.h>

// ---------------- AHT21 ----------------
Adafruit_AHTX0 aht;
Adafruit_Sensor *aht_humidity, *aht_temp;

// ---------------- ENS160 ----------------
// Fermion/combo boards default to I2C address 0x53.
// If your board's SDO/ADDR pin is tied to GND, use 0x52 instead.
DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/ 0x53);

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Wire.begin(21, 22); // SDA, SCL on ESP32

  // ---- Init AHT21 ----
  Serial.println("Initializing AHT21...");
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20/AHT21 chip - check wiring!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("AHT21 found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();
  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();

  // ---- Init ENS160 ----
  Serial.println("Initializing ENS160...");
  while (NO_ERR != ENS160.begin()) {
    Serial.println("Communication with ENS160 failed, please check connection");
    delay(3000);
  }
  Serial.println("ENS160 initialized!");

  ENS160.setPWRMode(ENS160_STANDARD_MODE);

  // Seed with a reasonable default until the first AHT21 reading comes in
  ENS160.setTempAndHum(/*temperature=*/25.0, /*humidity=*/50.0);
}

void loop() {
  // ---- Read AHT21 ----
  sensors_event_t humidity, temp;
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" deg C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" % rH");

  // ---- Feed live climate data into ENS160 for compensation ----
  ENS160.setTempAndHum(temp.temperature, humidity.relative_humidity);

  // ---- Read ENS160 ----
  uint8_t status = ENS160.getENS160Status();
  Serial.print("Sensor operating status: ");
  Serial.println(status); // 0=normal, 1=warm-up (first 3 min), 2=initial start-up (first hour, once ever)

  uint8_t aqi = ENS160.getAQI();
  Serial.print("Air Quality Index (1-5): ");
  Serial.println(aqi);

  uint16_t tvoc = ENS160.getTVOC();
  Serial.print("TVOC: ");
  Serial.print(tvoc);
  Serial.println(" ppb");

  uint16_t eco2 = ENS160.getECO2();
  Serial.print("eCO2: ");
  Serial.print(eco2);
  Serial.println(" ppm");

  Serial.println();
  delay(1000);
}