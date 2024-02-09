/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

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
void diagMove(movements *vals);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  movements motors;

  while(1)
  {
      motorVals(&motors);

      if(motors.forwardBackward != 0)
      {
        moveForwardBack(&motors);
      }

      if(motors.leftRight != 0)
      {
        moveLeftRight(&motors);
      }

      if(motors.strafeLeftRight != 0)
      {
        moveStrafe(&motors);
      }

      if(motors.LeftRight !)
  }
  
}

void motorVals(movements *vals)
{
  vals->forwardBackward = Controller1.Axis3.position(percent);
  vals->leftRight = Controller1.Axis4.position(percent);
  vals->strafeLeftRight = Controller1.Axis1.position(percent);
  vals->diagonalMovement = ((Controller1.))
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

    //Strafe!
    LeftFront.spin(forward);
    LeftRear.spin(reverse);
    RightFront.spin(reverse);
    RightRear.spin(forward);
  }

  else
  {
    //Set velocities
    LeftFront.setVelocity(vals->strafeLeftRight, percent);
    LeftRear.setVelocity(vals->strafeLeftRight, percent);
    RightFront.setVelocity(vals->strafeLeftRight, percent);
    RightRear.setVelocity(vals->strafeLeftRight, percent);

    //Strafe!
    LeftFront.spin(reverse);
    LeftRear.spin(forward);
    RightFront.spin(forward);
    RightRear.spin(reverse);
  }
}

void diagMove(movements *vals)
{

}