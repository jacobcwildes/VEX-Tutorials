/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Oct 05 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision4              vision        5               
// Drivetrain           drivetrain    20, 21          
// Controller1          controller                    
// Motor1               motor         10              
// Motor10              motor         1               
// Motor6               motor         7               
// Distance3            distance      3               
// GPS11                gps           11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  //tracking variables:
  int position = 0;
  int temp = 0;
  int power = 0;
  int vel = 0;
  int torque = 0;
  int batteryPercent = 0;
  int desiredPos = 0;
  int turn = 0;
  int forw = 0;
  int back = 0;
  int debugDrive = 0;
  float left = 0;
  float right = 0;
  float divisor = 1;

  //want ball in lower quarter of screen and then maintain center X. If it exists of course
  int ballPosx = 0;
  int ballPosY = 0;

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Brain.Screen.clearScreen();
  //Clear controller screen
  Controller1.Screen.clearScreen();
  
  //Run forever
  while(1)
  {
    desiredPos = Controller1.Axis3.position(percent); //useless motor
    turn = Controller1.Axis1.position(percent); //left/right
    forw = (int) Controller1.ButtonR1.pressing();
    back = (int) Controller1.ButtonR2.pressing();

    debugDrive = ((forw * 50) - (back * 50) + (turn * .4));

    left = ((forw * 50) - (back * 50) + (turn * .4));
    right = ((forw * 50) - (back * 50) - (turn * .4));

    if(abs((int) (left)) > abs((int) (right)))
    {
      divisor = left;
    }
    else divisor = right;

    left *= 100.0;
    left /= abs((int) divisor);
    right *= 100.0;
    right /= abs((int) divisor);
    Motor10.spin(forward);
    Motor10.setVelocity((int)left, percent);
    Motor1.spin(forward);
    Motor1.setVelocity((int)right, percent);
    Motor6.spinToPosition(((int) ((float) desiredPos * 3.6)), degrees);
    
    
    Brain.Screen.print("Forward: %d", forw);
    Brain.Screen.newLine();
    Brain.Screen.print("Backward: %d", back);
    Brain.Screen.newLine();
    Brain.Screen.print("Turn: %d", turn);
    Brain.Screen.newLine();
    Brain.Screen.print("Forward Vel: %d", debugDrive);
    Brain.Screen.newLine();
    Brain.Screen.clearLine();
    Brain.Screen.print("Left: %d", (int)left);
    Brain.Screen.newLine();
    Brain.Screen.clearLine();
    Brain.Screen.print("Right: %d", (int)right);
    Brain.Screen.newLine();
    Brain.Screen.clearLine();
    Brain.Screen.print("Divisor: %d", (int)divisor);
    Brain.Screen.newLine();
    Brain.Screen.clearLine();
    Brain.Screen.print("Desired Degree: %d", desiredPos);
    Brain.Screen.newLine();
    Brain.Screen.clearLine();
    Brain.Screen.print("Thing: %d", (int) ((float) desiredPos * 1.8) + 180);
    Brain.Screen.setCursor(1,1);

    //Grab sensor data
    temp = Motor6.temperature(percent);
    torque = Motor6.torque(InLb);
    batteryPercent = Brain.Battery.voltage();
    vel = Motor10.velocity(rpm);
    position = Motor6.position(degrees);
    power = Motor6.power();

    //Print to controller screen
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Temperature: %d", temp);
    Controller1.Screen.newLine();
    Controller1.Screen.print("Velocity: %d", vel);
   // Controller1.Screen.print("Torque: %d", torque);
    Controller1.Screen.newLine();
    Controller1.Screen.print("Battery: %d", batteryPercent);
    //Controller1.Screen.newLine();
 
    //Controller1.Screen.newLine();
    //Controller1.Screen.print("Position: %d", position);
    //Controller1.Screen.newLine();
    //Controller1.Screen.print("Power: %d", power);


    //Vision Sensor logic:


    Vision4.takeSnapshot(Vision4__SIG_1);
    //Is the ball in view?
    if(Vision4.objects[0].exists)
    {
      Brain.Screen.print("Ball detected");
      Brain.Screen.newLine();
      Brain.Screen.print("Ball X: %d", Vision4.objects[0].centerX);
      Brain.Screen.newLine();
      Brain.Screen.print("Ball Y: %d", Vision4.objects[0].centerY);
      Brain.Screen.newLine();
      Brain.Screen.print("Distance: %d (in)", Distance3.objectDistance(inches));
      //If the ball is too far away
      if(Distance3.objectDistance(inches) > 10) //Change this later after testing
      {
        
        Motor1.spin(forward);
        Motor10.spin(forward);
        Motor1.setVelocity(60, percent);
        Motor10.setVelocity(60, percent);

        if(Vision4.objects[0].centerX < 150) //Spin left if ball too far left
        {
          Motor1.spinFor(forward, 10, degrees);
          Motor10.spinFor(reverse, 10, degrees);
        }
        else if(Vision4.objects[0].centerX > 150) //Spin right if ball too far right
        {
          Motor1.spinFor(reverse, 10, degrees);
          Motor10.spinFor(forward, 10, degrees);
        }
        else
        {
          Motor1.spin(forward);
          Motor10.spin(forward);
          Motor1.setVelocity(60, percent);
          Motor10.setVelocity(60, percent);
        }
      }
      else
      {
        Motor6.spinFor(forward, 60, degrees);
      }

    }
    Motor6.stop();
  }
}