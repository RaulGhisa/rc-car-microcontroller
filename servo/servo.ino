int forward = 5;
int backward = 4;
int enable = 6;
int pot = 0;
int ref;
float P_CONSTANT = .48;
int it = 400;
int schreechingThreshold = 12;
 
int computeServoInput(int potInput, int ref) {
  Serial.println(potInput - ref);
  int result = (int)(P_CONSTANT * (potInput - ref));
  if (result > 255){
    return 255;
  }
  if (result < -255){
    return -255;
  }
  if (abs(result)<schreechingThreshold){
    return 0;
  }
  return result;
}
 
void steerAtRef (int ref) {
  int potInput = analogRead(pot);
  int command = computeServoInput(potInput, ref);
 
  digitalWrite(forward, command > 0);
  digitalWrite(backward, command < 0);
  analogWrite(enable, abs(command));
}
 
 
void setup() {
 
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(pot, INPUT);
 
  Serial.begin(9600);
}
 
void loop() {
  steerAtRef(ref);
  it++;
  Serial.println(ref);
  delay(50);
  if (it % 400 < 100){
    ref = 600;
  }
  else if(it%400 < 200){
    ref = 500;
  }
  else if(it%400 < 300){
    ref = 400;
  }
  else{
    ref = 500;
  }
}
