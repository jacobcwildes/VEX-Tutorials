/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Sep 14 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    10, 1           
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  int forwardBack = 0;

  int leftRight = 0;

  while(1)
  {
      forwardBack = Controller1.Axis3.position(percent);

      leftRight = Controller1.Axis1.position(percent);

      Drivetrain.setDriveVelocity(forwardBack, percent);

      Drivetrain.setTurnVelocity(leftRight, percent);
  }
  
}
