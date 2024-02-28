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
// Controller1          controller                    
// Ratchet              motor         5               
// Vision4              vision        19              
// Distance3            distance      18              
// Catapult             motor         6               
// Catapult2            motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "autonomy.h"
#include "unistd.h"
#include "cmath"

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
int deadZone = 5;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearScreen();
  Ratchet.setStopping(coast); //Make sure the ratchet motor can free spin
  Catapult.setStopping(coast);
  Catapult2.setStopping(coast);
  
  task::sleep(1000);//sleeps for 2 seconds

  int controllerTime = 0;

  int startRatchet = 0;
  int startCatapult = 0;


  movements motors;

  //Fetch starting Ratchet motor position
  startRatchet = Ratchet.position(degrees);
  startCatapult = Catapult.position(degrees);
  Ratchet.setStopping(coast); //Make sure the ratchet motor can free spin

  while(1)
  {
     Ratchet.setStopping(coast); //Make sure the ratchet motor can free spin
     //Brain.Screen.clearScreen();

      //if(controllerTime == 0)
      //{
      //  autonomy();
      //}

      
      motorVals(&motors);

      //if(motors.forwardBackward != 0)
      //{
        moveForwardBack(&motors);
       // controllerTime = 1;
      //}

      //if(motors.leftRight != 0)
      //{
        //moveLeftRight(&motors);
        //controllerTime = 1;
      //}

      //if(motors.strafeLeftRight != 0)
      //{
        //moveStrafe(&motors);
       // controllerTime = 1;
      //}

      if(Controller1.ButtonR2.pressing())
      {
        Ratchet.spinFor(forward, 15, degrees, false); //release motor to throw
        controllerTime = 1;
      }

      if(Controller1.ButtonR1.pressing())
      {
        Ratchet.spinToPosition(startRatchet, degrees, false); //Need to check motor direction
        Ratchet.setStopping(coast);
        controllerTime = 1;
      }

      if(Controller1.ButtonL2.pressing()) //Move to throw position
      {
        Catapult.setMaxTorque(100, percent);
        Catapult2.setMaxTorque(100, percent);
        Catapult.spinFor(-200, degrees, false);
        Catapult2.spinFor(-200, degrees, false);
        Catapult.setStopping(hold);
        Catapult2.setStopping(hold);     
      }

      if(Controller1.ButtonL1.pressing()) //Release
      {
        Catapult.setMaxTorque(100, percent);
        Catapult2.setMaxTorque(100, percent);
        Catapult.spinFor(300, degrees, false);
        Catapult2.spinFor(300, degrees, false);
        Catapult.setStopping(coast);
        Catapult2.setStopping(coast);
      }

      //Stop all motors if not getting input
      //Catapult.stop();
      //Ratchet.stop();
      //RightFront.stop();
      //RightRear.stop();
      //LeftFront.stop();
      //LeftRear.stop();

  }
  
}

void motorVals(movements *vals)
{
  //Get controller values
  vals->forwardBackward = Controller1.Axis3.position(percent);
  vals->leftRight = Controller1.Axis4.position(percent);
  vals->strafeLeftRight = Controller1.Axis1.position(percent);
  Brain.Screen.setCursor(1, 0);
  Brain.Screen.clearLine();
  Brain.Screen.print("Current forward/backward: %d", vals->forwardBackward);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Current left/right : %d", vals->leftRight);
  Brain.Screen.newLine();
  Brain.Screen.clearLine();
  Brain.Screen.print("Current strafe: %d", vals->strafeLeftRight);
}

void moveForwardBack(movements *vals)
{
    Brain.Screen.setCursor(5, 0);
    //Brain.Screen.newLine();
   // Brain.Screen.clearLine();
   // Brain.Screen.print("In forward back");

    int posSqrt = sqrt(pow(vals->leftRight, 2) + pow(vals->forwardBackward, 2));
    int negSqrt = -posSqrt;
    int turningSpeed13 = vals->forwardBackward-vals->leftRight;
    int turningSpeed24 = vals->forwardBackward+vals->leftRight;

    if(abs(vals->leftRight) < deadZone && abs(vals->forwardBackward) > deadZone) //Straight forward/backward condition
    {
      //Brain.Screen.newLine();
      //Brain.Screen.clearLine();
      //Brain.Screen.print("Go forward");
      LeftFront.setVelocity(vals->forwardBackward, percent);
      LeftRear.setVelocity(vals->forwardBackward, percent);
      RightFront.setVelocity(vals->forwardBackward, percent);
      RightRear.setVelocity(vals->forwardBackward, percent);
    }

    else if(abs(vals->leftRight) > deadZone && abs(vals->forwardBackward) < deadZone) //Hard left/right
    {
      //Brain.Screen.newLine();
      //Brain.Screen.print("Hard turn");
      //Set respective motor velocities
      LeftFront.setVelocity(vals->leftRight, percent);
      LeftRear.setVelocity(vals->leftRight, percent);
      RightFront.setVelocity(-vals->leftRight, percent); //Invert half motors
      RightRear.setVelocity(-vals->leftRight, percent);
    }
    //Brain.Screen.clearLine();
    else if(vals->leftRight > deadZone && vals->forwardBackward > deadZone) //Qaudrant 1 Turn to the right and still go forward
    {
      //Brain.Screen.newLine();
      //Brain.Screen.print("Quad 1");
      RightFront.setVelocity(turningSpeed13, percent);
      RightRear.setVelocity(turningSpeed13, percent);
      LeftFront.setVelocity(posSqrt, percent);
      LeftRear.setVelocity(posSqrt, percent);
    }
    //Brain.Screen.clearLine();
    else if(vals->leftRight < deadZone && vals->forwardBackward > deadZone) //Quadrant 2
    {
      //Brain.Screen.newLine();
      //Brain.Screen.print("Quad 2");
      RightRear.setVelocity(posSqrt, percent);
      RightFront.setVelocity(posSqrt, percent);
      LeftFront.setVelocity(turningSpeed24, percent);
      LeftRear.setVelocity(turningSpeed24, percent);
    }
    //Brain.Screen.clearLine();
    else if(vals->leftRight > deadZone && vals->forwardBackward < deadZone) //Quadrant 4
    {
      //Brain.Screen.newLine();
      //Brain.Screen.print("Quad 3");
      RightRear.setVelocity(negSqrt, percent);
      RightFront.setVelocity(negSqrt, percent);
      LeftFront.setVelocity(turningSpeed24, percent);
      LeftRear.setVelocity(turningSpeed24, percent);     
    }
    //Brain.Screen.clearLine();
    else if(vals->leftRight < deadZone && vals->forwardBackward < deadZone) //Quadrant 3
    {
      //Brain.Screen.newLine();
      //Brain.Screen.print("Quad 4");
      RightFront.setVelocity(turningSpeed13, percent);
      RightRear.setVelocity(turningSpeed13, percent);
      LeftFront.setVelocity(negSqrt, percent);
      LeftRear.setVelocity(negSqrt, percent); 
    }
    //Brain.Screen.clearLine();

/*
    //Set respective motor velocities
    LeftFront.setVelocity(vals->forwardBackward, percent);
    LeftRear.setVelocity(vals->forwardBackward, percent);
    RightFront.setVelocity(vals->forwardBackward, percent);
    RightRear.setVelocity(vals->forwardBackward, percent);
*/
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
      LeftFront.setVelocity(vals->forwardBackward - vals->leftRight, percent);
      LeftRear.setVelocity(vals->forwardBackward - vals->leftRight, percent);
      RightFront.setVelocity(vals->forwardBackward + vals->leftRight, percent);
      RightRear.setVelocity(vals->forwardBackward + vals->leftRight, percent);

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