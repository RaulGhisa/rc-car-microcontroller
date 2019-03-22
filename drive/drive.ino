#define MOTOR_B_ENABLE 6
#define MOTOR_B_BWD 7
#define MOTOR_B_FWD 8
#define SERVO_A_BWD 9
#define SERVO_A_FWD 10
#define SERVO_A_ENABLE 11

int throttle = 0;
int steer = 0;

enum {FWD, BWD, LEFT, RIGHT} dir;

typedef struct HBridge {
  int fwd;
  int bwd;
  int enable;
};

HBridge motor = {MOTOR_B_FWD, MOTOR_B_BWD, MOTOR_B_ENABLE};
HBridge serv = {SERVO_A_FWD, SERVO_A_BWD, SERVO_A_ENABLE};

void setup() {

  Serial.begin(9600);

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


  dir = FWD;
}

void loop() {

  digitalWrite(MOTOR_B_FWD, HIGH);
  digitalWrite(MOTOR_B_BWD, LOW);

  for (int i = 20; i < 200; i += 10) {
    drive(i);
    delay(1000);
  }

  for (int i = 10; i < 101; i += 10) {
    drive(i);
    delay(1000);
  }
}

void serialEvent() {

}


void drive(int x) {

  if (x < 51) dir = FWD;
  else dir = BWD;

  power(map(abs(x), 0, 51, 0, 200));
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
}
