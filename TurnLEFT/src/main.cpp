/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Nov 02 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor2               motor         2               
// Motor10              motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(1)
  {
    //Turn right
    Motor10.setVelocity(-20, percent);
    Motor2.setVelocity(20, percent);
    Motor10.spin(forward);
    Motor2.spin(forward);
    wait(5, seconds);
    Motor2.stop();
    Motor10.stop();
    wait(2, seconds);
    
    //Turn left
    Motor10.setVelocity(20, percent);
    Motor2.setVelocity(-20, percent);
    Motor10.spin(forward);
    Motor2.spin(forward);
    wait(5, seconds);
    Motor2.stop();
    Motor10.stop();
    wait(2, seconds);
  }
  
}
