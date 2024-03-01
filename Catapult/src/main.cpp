/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Feb 29 2024                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Catapult             motor         6               
// Catapult2            motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void catapultThrow(void);
void catapultReady(void);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.clearScreen();

  while(1)
  {
    if(Controller1.ButtonL2.pressing()) //Move to throw position
    {
      Brain.Screen.setCursor(1, 0);
      Brain.Screen.clearLine();
      Brain.Screen.print("Move to throw");
      catapultReady();
    }

    if(Controller1.ButtonL1.pressing()) //Throw!
    {
      catapultThrow();
    }
  
  }
}

void catapultReady(void)
{
  Catapult.setStopping(brake);
  Catapult2.setStopping(brake);

  Catapult.setMaxTorque(60, percent);
  Catapult2.setMaxTorque(60, percent);
  Catapult.setVelocity(60, percent);
  Catapult2.setVelocity(60, percent);

  Catapult.rotateFor(-200, degrees, false); //No wait for motors to spin
  Catapult2.rotateFor(-200, degrees, false);
}

void catapultThrow(void)
{
  Catapult.setStopping(coast);
  Catapult2.setStopping(coast);
  Catapult.spinFor(200, degrees, false); //No wait for motors to spin
  Catapult2.spinFor(200, degrees, false);
}