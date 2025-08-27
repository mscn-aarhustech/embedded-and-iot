#include <Wire.h>

void setup() {
  // Use Wire1 for the Qwiic/STEMMA QT port
  Wire1.begin(); 
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open
  Serial.println("\nI2C Scanner for Wire1 (Qwiic Port)");
}

void loop() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // Use Wire1 to check each address
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found on Wire1\n");
  else
    Serial.println("done\n");
  delay(5000); // Wait 5 seconds for next scan
}