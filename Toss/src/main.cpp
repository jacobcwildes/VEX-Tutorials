/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jacob Wildes                                              */
/*    Created:      Mon Jan 22 2024                                           */
/*    Description:  Simple project to make a catapult using                   */
/*                  two motors                                                */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Tosser               motor_group   1, 2            
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  /* Logic: If the button (R2) is pushed on the controller, want to go fully forward
  at 100% power (may be less after testing). If the R1 button is pushed,
  then the catapult will spin backward to the desired position */

  /* NOTE: The motor group is set up such that motor 1 spins forward, motor 2 spins in reverse
     This may change depending on physical requirements */

  /* Possible future TODO: 
  - Make a different button that allows the motors to simply spin.
  - Add another button that allows the user to set the "home" position manually
  */
  
  while(1)
  {
    
    if(Controller1.ButtonR2.pressing())
    {
      Tosser.setMaxTorque(100, percent); //This may change later, just super high to start
      Tosser.setVelocity(100, percent); //May change
      Tosser.setPosition(0, degrees); //In theory, tell motors they are "homed"
      Tosser.spinFor(forward, 120, degrees); //May want to change the degrees forward it spins
    }
    
    if(Controller1.ButtonR1.pressing())
    {
      Tosser.setMaxTorque(33, percent); //Returning home, so torque can be much lower
      Tosser.setVelocity(20, percent); //Speed can be much lower on return
      Tosser.spinFor(reverse, 120, degrees); //In theory, returns home
    }

    else
    {
      Tosser.stop();
    }

  }

}
