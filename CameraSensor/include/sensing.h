#include "controller.h"
struct SenseDat
{
  int position;
  int temp;
  int power;
  int vel;
  int torque;
  int batteryPercent;
};

void reportSense(SenseDat *sensorData, ConDat *controllerData);