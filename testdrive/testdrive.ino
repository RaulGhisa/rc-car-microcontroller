#define MOTOR_B_ENABLE 6
#define MOTOR_B_BWD 7
#define MOTOR_B_FWD 8
#define SERVO_A_BWD 9
#define SERVO_A_FWD 10
#define SERVO_A_ENABLE 11
#define SERVO_POT 0

String inputString = "";
char drive_string[10] = {'\0'};
int drive_string_pos = 0;
boolean stringComplete = false;

boolean should_init = true;

// servo

// led

int ref;
float P_CONSTANT = .55;
int it = 400;
int schreechingThreshold = 12;

int x_final = 0;
int y_final = 0;

int throttle = 0;
int steer = 0;

enum {FWD, BWD} dir;
//enum {LEFT, RIGHT} steer;

struct HBridge {
  int fwd;
  int bwd;
  int enable;
};

struct HBridge motor = {MOTOR_B_FWD, MOTOR_B_BWD, MOTOR_B_ENABLE};
struct HBridge serv = {SERVO_A_FWD, SERVO_A_BWD, SERVO_A_ENABLE};

int counter = 0;

//int format_string();
//void power(int pwm);
//void steerAtRef(int x);

int y = 0;
int x = 0;


void setup() {

  digitalWrite(MOTOR_B_FWD, LOW);
  digitalWrite(MOTOR_B_BWD, LOW);
  digitalWrite(SERVO_A_FWD, LOW);
  digitalWrite(SERVO_A_BWD, LOW);

  pinMode(MOTOR_B_FWD, OUTPUT);
  pinMode(MOTOR_B_BWD, OUTPUT);
  pinMode(MOTOR_B_ENABLE, OUTPUT);
  pinMode(SERVO_A_FWD, OUTPUT);
  pinMode(SERVO_A_BWD, OUTPUT);
  pinMode(SERVO_A_ENABLE, OUTPUT);

  pinMode(serv.fwd, OUTPUT);
  pinMode(serv.bwd, OUTPUT);
  pinMode(serv.enable, OUTPUT);
  pinMode(SERVO_POT, INPUT);

  digitalWrite(MOTOR_B_FWD, 1);
  digitalWrite(MOTOR_B_BWD, 0);

  Serial.begin(19200);

  dir = FWD;

  // UART
  inputString.reserve(200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void drive(int x, int y);

void loop() {
//  
//      while (mySerial.available()) {
//        char inChar = (char)mySerial.read();
//  
//        if (inChar != '\n') {
//          inputString += inChar;
////          Serial.println("received");
////          mySerial.println("received");
//
//
//        }
//        if (inChar == '\n') {
//          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//          Serial.println("received");
//          mySerial.println("received");
//          int no = format_string();
//          y = no & 0x00FF;
//          x = no >> 8;
//          inputString = "";
//        }
//      }

//      char str[] = {'c', 'e', 'v', 'a', '\n'};
//      char *str = "ceva\n";
//      Serial.print(str);
//      delay(1000);
//      Serial.print('\n');
//      drive(x, y);

  //  for (int i = 0; i < 100; i += 10) {
  //    drive(i, 50);
  //    delay(500);
  //  }
  //

//  dir = FWD;
//  power(255);
//  delay(3000);
//  power(0);
//  delay(1000);
//  
//  dir = BWD;
//  power(255);
//  delay(3000);
//  power(0);
//  delay(1000);

  for (int i = 5; i < 100; i += 10) {
    for (int j = 0; j < 50; j++) {
      steering(i);
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

  return atoi(chars);
}

void drive(int x, int y) {

  if (y >= 51) {
    y = y - 51;
    dir = FWD;
  }
  else {
    dir = BWD;
  }

  int pwm = map(y, 0, 50, 0, 255);
  power(pwm);
  steering(x);
}

void power(int pwm) {

  switch (dir) {
    case FWD :
      digitalWrite(motor.fwd, 1);
      digitalWrite(motor.bwd, 0);
      break;
    case BWD :
      digitalWrite(motor.fwd, 0);
      digitalWrite(motor.bwd, 1);
      break;
  }
  analogWrite(motor.enable, pwm);
  Serial.print("pwm: "); Serial.println(pwm);
}

int computeServoInput(int potInput, int ref) {
  int result = (int)(P_CONSTANT * (potInput - ref));
  if (result > 255) {
    return 255;
  }
  if (result < -255) {
    return -255;
  }
  if (abs(result) < schreechingThreshold) {
    return 0;
  }
  return result;
}

void steerAtRef (int ref) {
  int potInput = analogRead(SERVO_POT);
  Serial.print("potInput: "); Serial.println(potInput);
  int command = computeServoInput(potInput, ref);
  Serial.print("command / result: "); Serial.println(command);

  // 

  digitalWrite(serv.fwd, command < 0);
  digitalWrite(serv.bwd, command > 0);
  analogWrite(serv.enable, abs(command));
}

void steering(int x) {
  if (x < 51) {
    steerAtRef(map(x, 0, 50, 500, 620)); // left
  } else {
    steerAtRef(map(x, 51, 101, 500, 400)); // right
  }
}
