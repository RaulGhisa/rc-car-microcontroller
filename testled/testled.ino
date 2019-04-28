int state = 0;

void setup() {
  // 3 4

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A2, INPUT);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(500);

  int val = analogRead(A2);
  Serial.println(val);
  if (val > 300) {
    state = 1;
  } else {
    state = 0;
  }
  

  if (state == 1) {
    digitalWrite(4, HIGH);
    delay(500);
    digitalWrite(4, LOW);
  } else {
    digitalWrite(4, LOW);
  }

}
