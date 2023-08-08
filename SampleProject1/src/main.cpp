/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jacob Wildes                                              */
/*    Created:      Fri Jul 21 2023                                           */
/*    Description:  Sample project to make a robot move around                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/* IMPORTANT NOTES:                                                           */
/* In the automatically generated source tree, in folder "src", the "robot-config.cpp" */
/* is generated for us via the config GUI. It can be unlocked for manual editing later */


/* TOOLTIPS:  */
/* In order to add devices, navigate to the top right corner underneath the minimize button */
/* to the icon that looks like an ethernet port */
/* It is strongly advised to change the name of the devices being made so that it isn't */
/* confusing which device is about to be used */


/* HOW TO: */
/* Every robot has the same base. It needs a controller setup, and drivetrain  */
/* Start by clicking on "Add a device". A list will appear. For this tutorial, */
/* select the 2-motor drivetrain and select ports 1 and 2 for the left and right */
/* motors respectively. On the third screen, select "No Gyro". On the final screen */
/* There are options for different sized wheels, tracks, wheelbase, Gear Ratio, and */
/* Gear Cartridge. Since this is a very basic tutorial, simply leave these as defaults and */
/* Select "DONE" After this is done, you will see a drivetrain show up in the device list, as */
/* well as in the "robot-config.cpp". */

/* Next, set up the controller by repeating the above steps and selecting "Controller". On the */
/* next screen you will see a list of the buttons to map to actions. For this tutorial, select the */
/* left joystick. On the first click, you will see it turn blue. To the left it wil show the   */
/* drivetrain icon with arrows facing forward and back, left and right. Click the icon again  */
/* and the same icon moves over to the right joystick. Clicking one more time splits forward and back */
/* to the left joystick, and left/right to the right joystick. For our purposes, we will use this configuration */
/* but feel free to use any configuration you want. With the desired layout selected, click "DONE" */
/* and the controller device will be added to the configuration of the program! */



// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10           
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    //Add logic

    //We know we want to make the robot go forward/backward, left/right.
    //To accomplish this, we need to execute everything based off of controller inputs.
      
    //Use this to store how far forward/backward we're pushing on the left joystick
    //Set to 0 for preallocation
    int forwardbackDirection = 0;

    //Use this to store how far left/right we're pushing the right joystick
    int leftrightDirection = 0;


    //Using a while loop to make sure this goes forever
    while(1){

      //Axis 3 is up/down on the left toggle - forwardbackDirection stores the percent forward/back
      forwardbackDirection = Controller1.Axis3.position(percent);

      //Axis 1 is left/right on the right toggle - lefrightDirection stores the percent left/right
      leftrightDirection =  Controller1.Axis1.position(percent);

      //This function uses the percentage taken from forwardbackDirection and translates it to movement
      Drivetrain.setDriveVelocity((-1 * forwardbackDirection), percent);

      //This function sets the turn velocity when the motors are running. This is a weird function
      //because it only makes the motors turn IF the left toggle is already moving forward or backward.
      //If the motor is not already spinning, the function does nothing.
      Drivetrain.setTurnVelocity(leftrightDirection, percent);
    }
}
