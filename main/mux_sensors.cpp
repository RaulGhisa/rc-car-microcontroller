#include "mux_sensors.h"
#include "Wire.h"
#include <VL53L0X.h>

uint8_t VL53[] = {2, 3, 4, 5};

void tcaselect(int i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setupSensors() {
  Wire.begin();
  
  for (int index = 0; index < VL_NO; index++){
    tcaselect(VL53[index]);
    delay(30);
    VL53L0X sensor;
    sensor.init();
    sensor.setTimeout(500);
    sensor.startContinuous();
  }
}

int getMuxDistanceReading(int sensorIndex) {
    tcaselect(VL53[sensorIndex]);
    VL53L0X sensor;
    return sensor.readRangeContinuousMillimeters();
}
