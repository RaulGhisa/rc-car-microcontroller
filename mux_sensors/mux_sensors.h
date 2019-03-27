#define TCAADDR 0x70
#define VL_NO 2

void tcaselect(int i);

void setupSensors();

int getMuxDistanceReading(int sensorIndex); 
