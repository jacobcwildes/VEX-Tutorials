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
void moveStrafe(movements *vals);
void simpleAutonomy(void);
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

  //Spin catapult down to go under pole
  Catapult.setMaxTorque(100, percent);
  Catapult2.setMaxTorque(100, percent);
  Catapult.spinFor(-200, degrees, false);
  Catapult2.spinFor(-200, degrees, false);
  task::sleep(5000);
  Catapult.setVelocity(-25, percent);
  Catapult2.setVelocity(-25, percent);
  //Catapult.spin(forward);
  //Catapult.spin(forward);
  //Catapult.setStopping(coast);
  //Catapult2.setStopping(coast);
  //task::sleep(1000);//sleeps for .5 second     
  Ratchet.spinToPosition(startRatchet, degrees, false); //Need to check motor direction
  Ratchet.setStopping(coast);

  simpleAutonomy();

  Ratchet.spinFor(forward, 30, degrees); //release motor to throw and block
  task::sleep(500);//sleeps for .5 second
  Catapult.setMaxTorque(100, percent);
  Catapult2.setMaxTorque(100, percent);
  Catapult.setVelocity(100, percent);
  Catapult2.setVelocity(100, percent);
  Catapult.spinToPosition(startCatapult, degrees, false);
  Catapult2.spinToPosition(startCatapult, degrees, false);
  Catapult.setStopping(coast);
  Catapult2.setStopping(coast);

  while(1)
  {
     Ratchet.setStopping(coast); //Make sure the ratchet motor can free spin
     //Brain.Screen.clearScreen();

      /*
      if(controllerTime == 0)
      {
        autonomy();
      }
      */
      
      motorVals(&motors);

      if(motors.forwardBackward != 0 || motors.leftRight != 0)
      {
        moveForwardBack(&motors);
        controllerTime = 1;
      }


      if(motors.strafeLeftRight != 0)
      {
        moveStrafe(&motors);
        controllerTime = 1;
      }

      if(Controller1.ButtonL2.pressing()) //Move to throw position
      {
        Catapult.setMaxTorque(100, percent);
        Catapult2.setMaxTorque(100, percent);
        Catapult.spinFor(-200, degrees, false);
        Catapult2.spinFor(-200, degrees, false);
        Catapult.setVelocity(-25, percent);
        Catapult2.setVelocity(-25, percent);
        //Catapult.spin(forward);
        //Catapult.spin(forward);
        Catapult.setStopping(coast);
        Catapult2.setStopping(coast);
        //task::sleep(1000);//sleeps for .5 second     
        Ratchet.spinToPosition(startRatchet, degrees, false); //Need to check motor direction
        Ratchet.setStopping(coast);
      }

      if(Controller1.ButtonL1.pressing()) //Release
      {
        Ratchet.spinFor(forward, 30, degrees); //release motor to throw and block
        task::sleep(500);//sleeps for .5 second
        Catapult.setMaxTorque(100, percent);
        Catapult2.setMaxTorque(100, percent);
        Catapult.setVelocity(100, percent);
        Catapult2.setVelocity(100, percent);
        Catapult.spinToPosition(startCatapult, degrees, false);
        Catapult2.spinToPosition(startCatapult, degrees, false);
        Catapult.setStopping(coast);
        Catapult2.setStopping(coast);
      }

      if(motors.strafeLeftRight == 0 && motors.leftRight == 0 && motors.forwardBackward == 0)
      {
        LeftFront.stop();
        LeftRear.stop();
        RightFront.stop();
        RightRear.stop();
      }

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

void moveStrafe(movements *vals)
{
  if(vals->strafeLeftRight > 0) //Strafe right
  {
    //Set velocities
    LeftFront.setVelocity(vals->strafeLeftRight, percent);
    LeftRear.setVelocity(-vals->strafeLeftRight, percent);
    RightFront.setVelocity(-vals->strafeLeftRight, percent);
    RightRear.setVelocity(vals->strafeLeftRight, percent);

    //Strafe right
    LeftFront.spin(forward);
    LeftRear.spin(forward);
    RightFront.spin(forward);
    RightRear.spin(forward);
  }

  if(vals->strafeLeftRight < 0) //Strafe Left
  {
    //Set velocities
    LeftFront.setVelocity(vals->strafeLeftRight, percent);
    LeftRear.setVelocity(-vals->strafeLeftRight, percent);
    RightFront.setVelocity(-vals->strafeLeftRight, percent);
    RightRear.setVelocity(vals->strafeLeftRight, percent);

    //Strafe left
    LeftFront.spin(forward);
    LeftRear.spin(forward);
    RightFront.spin(forward);
    RightRear.spin(forward);
  }
}

void simpleAutonomy(void)
{
  //Go forward into ball THIS WILL NEED TO BE CHANGED BASED ON HOW FAR BALL IS FROM BOT @ START
  LeftFront.spinFor(forward, 6, turns, false);
  RightFront.spinFor(forward, 6, turns, false);
  RightRear.spinFor(forward, 6, turns, false);
  LeftRear.spinFor(forward, 6, turns, false);
  
  task::sleep(7000);
  
  //Turn 45* to left
  RightFront.spinFor(forward, 2, turns, false);
  RightRear.spinFor(forward, 2, turns, false);
  
  task::sleep(4000);
  
  //Go forward to goal
  LeftFront.spinFor(forward, 6, turns, false);
  RightFront.spinFor(forward, 6, turns, false);
  RightRear.spinFor(forward, 6, turns, false);
  LeftRear.spinFor(forward, 6, turns, false);

  task::sleep(7000);

  //Go forward into ball THIS WILL NEED TO BE CHANGED BASED ON HOW FAR BALL IS FROM BOT @ START
  LeftFront.spinFor(forward, -6, turns, false);
  RightFront.spinFor(forward, -6, turns, false);
  RightRear.spinFor(forward, -6, turns, false);
  LeftRear.spinFor(forward, -6, turns, false);
  
  task::sleep(7000);
  
  //Turn 45* to left
  RightFront.spinFor(forward, -2, turns, false);
  RightRear.spinFor(forward, -2, turns, false);
  
  task::sleep(4000);
  
  //Back to elevation bar
  LeftFront.spinFor(forward, -6, turns, false);
  RightFront.spinFor(forward, -6, turns, false);
  RightRear.spinFor(forward, -6, turns, false);
  LeftRear.spinFor(forward, -6, turns, false);

  task::sleep(7000);
}