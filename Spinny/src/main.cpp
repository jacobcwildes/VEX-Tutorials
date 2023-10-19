/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Oct 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(1)
  {
    if(Controller1.ButtonUp.pressing())
    {
            Motor1.setVelocity(100, percent);
      Motor1.spin(forward);
    }
    else if(Controller1.ButtonDown.pressing())
    {
      Motor1.spin(reverse);
      Motor1.setVelocity(100, percent);
    }
  }
  
}
