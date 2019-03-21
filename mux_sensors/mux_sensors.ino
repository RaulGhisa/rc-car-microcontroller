#include "Wire.h"
extern "C" {
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#include "Adafruit_VL53L0X.h"

#define TCAADDR 0x70
#define VL_NO 3

uint8_t VL53[] = {2, 6, 7};

void setup() {

  Wire.begin();

  Serial.begin(115200);

  scanner();
}

void loop() {

  print_dist();
  delay(1000);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void scanner() {
  while (!Serial);
  delay(1000);

  Wire.begin();

  Serial.begin(115200);
  Serial.println("\nTCAScanner ready!");

  for (uint8_t t = 0; t < 8; t++) {
    tcaselect(t);
    Serial.print("TCA Port #"); Serial.println(t);

    for (uint8_t addr = 0; addr <= 127; addr++) {
      if (addr == TCAADDR) continue;

      uint8_t data;
      if (! twi_writeTo(addr, &data, 0, 1, 1)) {
        Serial.print("Found I2C 0x");  Serial.println(addr, HEX);
      }
    }
  }

  Serial.println("\ndone");
}

void print_dist() {
  
  for (uint8_t t = 0; t < 3; t++) {
    tcaselect(VL53[t]);
    Serial.print("TCA Port #"); Serial.println(VL53[t]);

    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
    if (!lox.begin()) {
      Serial.println(F("Failed to boot VL53L0X"));
      while (1);
    }
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
      Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    } else {
      Serial.println(" out of range ");
    }
  }
}
