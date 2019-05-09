#include "comm.h"
#include "Arduino.h"

String inputString = "";

void sendData(int *sensorData, int dataSize) {
  for (int i = 0; i < dataSize; i++) Serial.print(sensorData[i]);
  Serial.println();
}

void setupComm() {
  inputString.reserve(200);
}

int readData() {
  char inChar;
  int no = 0;

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
