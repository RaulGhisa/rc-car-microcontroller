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

  while (mySerial.available()) {
    char inChar = (char)mySerial.read();
    if (inChar != '\n')
      inputString += inChar;
    if (inChar == '\n') {
      Serial.println(inputString);
      int no = format_string(); 
      int y = no & 0x00FF;
      int x = no >> 8;
      
      Serial.print("x = "); Serial.println(x);
      Serial.print("y = "); Serial.println(y);
      
      Serial.println(no);
      inputString = "";
    }
  }

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

  Serial.println(chars);
  return atoi(chars);
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
