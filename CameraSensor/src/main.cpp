/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Oct 05 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision4              vision        5               
// Drivetrain           drivetrain    20, 21          
// Controller1          controller                    
// Motor1               motor         10              
// Motor10              motor         2               
// Motor6               motor         7               
// Distance3            distance      3               
// Inertial16           inertial      16              
// GPS14                gps           14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <math.h>
#include "autonomy.h"
#include "sensing.h"

using namespace vex;

int main() {

  ConDat controllerData;
  SenseDat sensorData;
  imuDat imuData;

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Brain.Screen.clearScreen();
  //Clear controller screen
  Controller1.Screen.clearScreen();
  
  int controllerTime = 0;

  //Run forever
  while(1)
  {
    if(controllerTime == 0)
    {
      autonomy(&imuData);
    }
   
    if(abs(Controller1.Axis3.position(percent)) > 0 || abs(Controller1.Axis1.position(percent)) > 0 || controllerTime == 1)
    {
      controllerTime = controllerUse(&controllerData);
    }

    if(controllerTime == 1)
    {
      reportSense(&sensorData, &controllerData);
    }

  }
}