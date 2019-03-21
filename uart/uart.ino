String inputString = "";
char drive_string[10] = {'\0'};
int drive_string_pos = 0;
boolean stringComplete = false;
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
  inputString.reserve(200);

  pinMode(4, OUTPUT);

  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
}
void loop() {

  //  mySerial.write("sugi pula, bolaj\n");

  if (mySerial.available()) {
    
    Serial.write(mySerial.read());
  }

  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void ceva() {

  if (stringComplete) {
    Serial.println(inputString);
    digitalWrite(4, HIGH);
    inputString = "";
    stringComplete = false;

    //delay(1000);
    digitalWrite(4, LOW);
  }
}

void serialEvent() {

}
