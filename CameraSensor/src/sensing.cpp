#include "vex.h"
#include "sensing.h"

using namespace vex;

void reportSense(SenseDat *sensorData, ConDat *controllerData)
{
  Brain.Screen.clearScreen();
  Brain.Screen.print("Forward: %d", (*controllerData).forw);
  Brain.Screen.newLine();
  Brain.Screen.print("Backward: %d", (*controllerData).back);
  Brain.Screen.newLine();
  Brain.Screen.print("Turn: %d", (*controllerData).turn);
  Brain.Screen.newLine();
  Brain.Screen.print("Forward Vel: %d", (*controllerData).debugDrive);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Left: %d", (int)(*controllerData).left);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Right: %d", (int)(*controllerData).right);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Divisor: %d", (int)(*controllerData).divisor);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Desired Degree: %d", (*controllerData).desiredPos);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Thing: %d", (int) ((float) (*controllerData).desiredPos * 1.8) + 180);
  Brain.Screen.setCursor(1,1);

  //Grab sensor data
  sensorData->temp = Motor6.temperature(percent);
  sensorData->torque = Motor6.torque(InLb);
  sensorData->batteryPercent = Brain.Battery.voltage();
  sensorData->vel = Motor10.velocity(rpm);
  sensorData->position = Motor6.position(degrees);
  sensorData->power = Motor6.power();

  //Print to controller screen
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Temperature: %d", (*sensorData).temp);
  Controller1.Screen.newLine();
  Controller1.Screen.print("Velocity: %d", (*sensorData).vel);
  // Controller1.Screen.print("Torque: %d", torque);
  Controller1.Screen.newLine();
  Controller1.Screen.print("Battery: %d", (*sensorData).batteryPercent);
}
