#define TCAADDR 0x70
#define VL_NO 2

void encoderTrigger();

void tcaselect(int i);

void setupSensors();

int getMuxDistanceReading(int sensorIndex); 

void getVelocity();
