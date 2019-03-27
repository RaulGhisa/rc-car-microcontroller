#include "mux_sensors.h"

void setup(){
  setupSensors();
  Serial.begin(115200);
}

void loop(){
  for (int t = 0; t<VL_NO; t++){
    Serial.println(t);
    Serial.println(getMuxDistanceReading(t));
  }
}
