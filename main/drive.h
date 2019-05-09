void setupDrive();

int computeServoInput(int potInput, int ref);

void steerAtRef (int ref);

void steering(int x);

void power(int pwm);

void drive(int steeringVariable, int speedVariable);
