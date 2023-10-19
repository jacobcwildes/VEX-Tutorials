/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\woody                                            */
/*    Created:      Thu Sep 21 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    21, 20          
// Controller1          controller                    
// Motor1               motor         1               
// Motor10              motor         10              
// Motor6               motor         6               
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
    forw = (int) Controller1.ButtonR2.pressing();
    back = (int) Controller1.ButtonR1.pressing();

    debugDrive = ((forw * 50) - (back * 50) + (turn * .4));

    left = ((forw * 50) - (back * 50) - (turn * .4));
    right = ((forw * 50) - (back * 50) + (turn * .4));

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
  }
}
