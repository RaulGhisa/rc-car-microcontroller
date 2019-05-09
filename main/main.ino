#include "TimerOne.h"

#include "mux_sensors.h"
#include "drive.h"
#include "comm.h"

#define BATTERY_PIN 14

#define RED 7
#define BLUE 6

//String inputString = "";
char drive_string[10] = { '\0' };
int drive_string_pos = 0;
boolean stringComplete = false;

int x;
int y;

void setup() {
  setupSensors();
  setupDrive();
  setupComm();

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sendStatus);

  Serial.begin(19200);

  pinMode(BATTERY_PIN, INPUT);
}

int sensorData[5] = {100, 110, 120, 200, 320};

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

  // read commands


  //  if (Serial.available()) {
  //    char inChar = (char)Serial.read();
  //
  //    if (inChar != '\n') {
  //      inputString += inChar;
  //    }
  //    else {
  //      int no = format_string();
  //      int y = no & 0x00FF;
  //      int x = no >> 8;
  //
  //      inputString = "";
  //    }
  //  }

  // update steering and power
  //  drive(50, 50);


  // read sensor + battery
  //  for (int i = 0; i < VL_NO; i++) {
  //    sensorData[i] = getMuxDistanceReading(i);
  //  }
  //  float batteryVolt = map(analogRead(BATTERY_PIN), 0, 1023, 6, 8.84);
  //
  //  // send to Serial
  //  for (int i = 0; i < sizeof(sensorData); i++) {
  //    Serial.println(sensorData[0]);
  //  }
  //  Serial.println(batteryVolt);

  for (int i = 5; i < 100; i += 10) {
    for (int j = 0; j < 50; j++) {
      steering(i);
    }
  }
}

void sendStatus() {
  sendData(sensorData, sizeof(sensorData) / sizeof(int));
}

void serialEvent() {
  int data = readData();

  Serial.println(data);
  
  if (data == 29000) {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);

    return;
  } else if (data == 29001) {
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);

    return;
  }

  y = data & 0x00FF;
  x = data >> 8;
}
