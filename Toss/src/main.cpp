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
// Tosser               motor_group   8, 19           
// Controller1          controller                    
// Drivetrain           drivetrain    1, 9, 2, 10     
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
  
  int forwardbackDirection = 0;

  int leftrightDirection = 0;

  while(1)
  {

    leftrightDirection = Controller1.Axis1.position(percent);
    forwardbackDirection = Controller1.Axis3.position(percent);

    if(forwardbackDirection)
    {
      Drivetrain.setDriveVelocity(forwardbackDirection, percent);
      Drivetrain.drive(forward);
    }

    if(leftrightDirection)
    {
      Drivetrain.setTurnVelocity(leftrightDirection, percent);
      Drivetrain.turn(right);
    }

    if(Controller1.ButtonR2.pressing())
    {
      Tosser.setMaxTorque(70, percent); //This may change later, just super high to start
      Tosser.setVelocity(70, percent); //May change
      Tosser.setPosition(0, degrees); //In theory, tell motors they are "homed"
      Tosser.spinFor(forward, 120, degrees); //May want to change the degrees forward it spins
    }
    
    if(Controller1.ButtonR1.pressing())
    {
      Tosser.setMaxTorque(50, percent); //Returning home, so torque can be much lower
      Tosser.setVelocity(50, percent); //Speed can be much lower on return
      Tosser.spinFor(reverse, 120, degrees); //In theory, returns home
    }

    else
    {
      Tosser.stop();
    }

  }

}
