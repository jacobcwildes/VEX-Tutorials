/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jacob Wildes                                              */
/*    Created:      Thu Feb 08 2024                                           */
/*    Description:  File to run the omniwheels                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFront            motor         1               
// LeftRear             motor         2               
// RightFront           motor         3               
// RightRear            motor         4               
// Drivetrain           drivetrain    21, 20          
// Controller1          controller                    
// Ratchet              motor         5               
// Vision4              vision        6               
// Distance3            distance      7               
// Catapult             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "autonomy.h"

using namespace vex;

struct movements{
  int forwardBackward = 0; //Standard forward/back
  int leftRight = 0; //Store left/right SPIN
  int strafeLeftRight = 0; //Strafe
  int diagonalMovement = 0; //Diagonal
};

void motorVals(movements *vals);
void moveForwardBack(movements *vals);
void moveLeftRight(movements *vals);
void moveStrafe(movements *vals);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearScreen();

  int controllerTime = 0;

  int startRatchet = 0;
  int startCatapult = 0;

  movements motors;

  //Fetch starting Ratchet motor position
  startRatchet = Ratchet.position(degrees);
  startCatapult = Catapult.position(degrees);

  while(1)
  {

      if(controllerTime == 0)
      {
        autonomy();
      }

      
      motorVals(&motors);

      if(motors.forwardBackward != 0)
      {
        moveForwardBack(&motors);
        controllerTime = 1;
      }

      if(motors.leftRight != 0)
      {
        moveLeftRight(&motors);
        controllerTime = 1;
      }

      if(motors.strafeLeftRight != 0)
      {
        moveStrafe(&motors);
        controllerTime = 1;
      }

      if(Controller1.ButtonR2.pressing())
      {
        Ratchet.spinFor(reverse, 2, degrees); //release motor to throw
        controllerTime = 1;
      }

      if(Controller1.ButtonR1.pressing())
      {
        Ratchet.spinToPosition(startRatchet, degrees); //Need to check motor direction
        Ratchet.setStopping(hold);
        controllerTime = 1;
      }

      if(Controller1.ButtonL2.pressing())
      {
        Catapult.spinToPosition(startCatapult - 100, degrees);
        Catapult.setStopping(hold);
      }

      if(Controller1.ButtonL1.pressing())
      {
        Catapult.spinToPosition(startCatapult, degrees);
        Catapult.setStopping(hold);
      }

      //Stop all motors if not getting input
      Catapult.stop();
      Ratchet.stop();
      RightFront.stop();
      RightRear.stop();
      LeftFront.stop();
      LeftRear.stop();

  }
  
}

void motorVals(movements *vals)
{
  //Get controller values
  vals->forwardBackward = Controller1.Axis3.position(percent);
  vals->leftRight = Controller1.Axis4.position(percent);
  vals->strafeLeftRight = Controller1.Axis1.position(percent);
}

void moveForwardBack(movements *vals)
{
    //Set respective motor velocities
    LeftFront.setVelocity(vals->forwardBackward, percent);
    LeftRear.setVelocity(vals->forwardBackward, percent);
    RightFront.setVelocity(vals->forwardBackward, percent);
    RightRear.setVelocity(vals->forwardBackward, percent);

    //Make motors spin
    LeftFront.spin(forward);
    LeftRear.spin(forward);
    RightFront.spin(forward);
    RightRear.spin(forward);
}

void moveLeftRight(movements *vals)
{
    if(vals->leftRight > 0) //Want to turn right
    {
      //Set proper velocities
      LeftFront.setVelocity(vals->leftRight, percent);
      LeftRear.setVelocity(vals->leftRight, percent);
      RightFront.setVelocity(vals->leftRight, percent);
      RightRear.setVelocity(vals->leftRight, percent);

      //Turn right
      LeftFront.spin(forward);
      LeftRear.spin(forward);

      //These two need to be in reverse to turn properly
      RightFront.spin(reverse);
      RightRear.spin(reverse);
    }

    else //Otherwise turn left
    {
      //Set proper velocities
      LeftFront.setVelocity(vals->leftRight, percent);
      LeftRear.setVelocity(vals->leftRight, percent);
      RightFront.setVelocity(vals->leftRight, percent);
      RightRear.setVelocity(vals->leftRight, percent);

      //Turn left
      LeftFront.spin(reverse);
      LeftRear.spin(reverse);

      //These two need to be in reverse to turn properly
      RightFront.spin(forward);
      RightRear.spin(forward);
    }
}

void moveStrafe(movements *vals)
{
  if(vals->strafeLeftRight > 0) //Strafe right
  {
    //Set velocities
    LeftFront.setVelocity(vals->strafeLeftRight, percent);
    LeftRear.setVelocity(vals->strafeLeftRight, percent);
    RightFront.setVelocity(vals->strafeLeftRight, percent);
    RightRear.setVelocity(vals->strafeLeftRight, percent);

    //Strafe right
    LeftFront.spin(forward);
    LeftRear.spin(reverse);
    RightFront.spin(reverse);
    RightRear.spin(forward);
  }

  else //Straft Left
  {
    //Set velocities
    LeftFront.setVelocity(vals->strafeLeftRight, percent);
    LeftRear.setVelocity(vals->strafeLeftRight, percent);
    RightFront.setVelocity(vals->strafeLeftRight, percent);
    RightRear.setVelocity(vals->strafeLeftRight, percent);

    //Strafe left
    LeftFront.spin(reverse);
    LeftRear.spin(forward);
    RightFront.spin(forward);
    RightRear.spin(reverse);
  }
}