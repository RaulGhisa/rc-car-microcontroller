#include "drive.h"
#include "comm.h"
#include "mux_sensors.h"

int steeringCommand;
int tractionCommand;

void setup() {
  setupSensors();
  setupDrive();
  setupComm();
}

void loop() {
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

  /*
  for (int i = 5; i < 100; i += 10) {
    for (int j = 0; j < 50; j++) {
      steering(i);
    }
  } 
  */
  int data = readSerialData();
  if (data != 29000 && data!=29001 && data!= -1){
    tractionCommand = data & 0x00FF;
    steeringCommand = data >> 8;
  }
  drive(steeringCommand, tractionCommand);
  delay(50);
}
