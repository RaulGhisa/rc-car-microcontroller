#include "mux_sensors.h"

void setup(){
  setupSensors();
  Serial.begin(9600);
}

void loop(){
  for (int t = 0; t<VL_NO; t++){
    Serial.print(t); Serial.print(": ");
    Serial.println(getMuxDistanceReading(t));
  }
}
