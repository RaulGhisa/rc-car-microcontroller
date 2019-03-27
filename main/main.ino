#include "mux_sensors.h"
#include "drive.h"

void setup(){
  setupSensors();
  setupDrive();
  Serial.begin(115200);
}

int dir = 0;

void loop(){
    // 1. Read commands from RPi (Serial)
    // 2. Update steering and power variables (x, y)
    // 3. drive(x,y);
    // 4. Read sensors
    //  for (int t = 0; t<VL_NO; t++){
    //    getMuxDistanceReading(t); -> update output buffer byte[]
    //  }
    // * ranging sensors
    // * battery sensor
    // 5. Write buffer on Serial
    // 6. delay(50);

    
    drive(51,50);
    delay(100);
}
