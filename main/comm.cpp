#define RED 13 // competitor 1
#define BLUE 12 // competitor 2
#define WHITE 5 // charging LED

#define CHARGING_PIN A2

#include "comm.h"
#include "Arduino.h"
#include "mux_sensors.h"
#include "TimerOne.h"
#include "drive.h"

String inputString = "";
bool batteryLedStatus = 0;

typedef struct {
  int16_t distanceSensorData[VL_NO];
  int16_t batteryVoltage;
  int16_t velocity;
  int16_t motorPwm;
  int16_t servoPwm;
} SensorData;

typedef union {
  SensorData sensors;
  byte serializedSensor[sizeof(SensorData)];
} SerializedSensorData;

void sendStatus() {
  // read sensors + battery
  SerializedSensorData sensorData;
  for (int i = 0; i < VL_NO; i++) {
    sensorData.sensors.distanceSensorData[i] = getMuxDistanceReading(i);
  }

  sensorData.sensors.batteryVoltage = getBatteryLevel();
  sensorData.sensors.velocity = getVelocity();
  sensorData.sensors.motorPwm = getThrottlePwm();
  sensorData.sensors.servoPwm = getSteerPwm();
  // send to Serial
  Serial.write(sensorData.serializedSensor, sizeof(sensorData));

  // blink charging LED
  if (digitalRead(CHARGING_PIN) == HIGH) {
    batteryLedStatus = ~batteryLedStatus;
  }
  else{
    batteryLedStatus = 0;
  }
  digitalWrite(WHITE, batteryLedStatus);
}

void setupComm() {
  inputString.reserve(200);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(CHARGING_PIN, INPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sendStatus);

  Serial.begin(19200);
}

int readSerialData() {
  int data = readData();
  
  if (data == 29000) {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
  } else if (data == 29001) {
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);
  }

  return data;
}

int readData() {
  char inChar;
  int no = -1;

  while (Serial.available()) {
    inChar = (char) Serial.read();

    if (inChar != '\n') {
      inputString += inChar;
    }
    else {
      no = format_string();

      inputString = "";
    }
  }

  return no;
}

int format_string() {
  char chars[20];
  int i = 0;
  int j = 0;
  while (inputString.charAt(i) < '0' || inputString.charAt(i) > '9') {
    i++;
  }

  for (int k = i; k < inputString.length(); k++) {
    chars[j++] = inputString.charAt(k);
  }
  chars[j] = '\0';

  return atoi(chars);
}
