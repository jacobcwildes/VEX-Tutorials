/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jacob Wildes                                              */
/*    Created:      Tue Aug 08 2023                                           */
/*    Description:  Display some sensor information on the robot              */
/*                  and controller                                            */                                                
/*                                                                            */
/*----------------------------------------------------------------------------*/

/* IMPORTANT NOTES: */
/* This tutorial builds on the previous tutorial, if anything is unclear, please go back */
/*    to the previous tutorial */


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

    //This variable stores how many times the left toggle has been pushed forward/backward
    int leftTogglePush = 0;

    //This variable stores how mamy times the right toggle was pushed left/right
    int rightTogglePush = 0;

    //This variable will hold the floating point (i.e. 2.3) value that the left toggle was pushed on a given axis
    float leftTogglePercent = 0;

    //This variable will hold the floating point value that the right toggle was pushed on a given axis
    float rightTogglePercent = 0;

    //Battery life remaining is stored in this variable
    float batteryPercent = 0;

    //Store the velocity of the drivetrain
    float drivetrainVelocity = 0;

    //Stores the amount of current - in 0-100% that the drivetrain is pulling
    float drivetrainCurrent = 0;

    //Stores the temperature of the drivetrain on a 0-100% scale. If this ever reaches 100%, that drivetrain is in trouble
    float drivetrainTemp = 0;

    //THIS SECTION DEALS WITH THE CONTROLLER SCREEN SETUP
    /*-------------------------------------------------------------------------------------------------------------------------*/
    //Since we're going to display information on the controller, we want to clear it out first
    //This step may not be necessary, but it is good practice to explicitly destroy unused things that will be overwritten
    Controller1.Screen.clearScreen();

    //Set the cursor to the top left corner of the controller screen with a small buffer on the top and left
    //This only needs to be done once at startup, so it is outside the while loop
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Left Joystick position: ", leftTogglePercent);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Right Joystick position: ", rightTogglePercent);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Left Joystick pushed ", leftTogglePush); Controller1.Screen.print(" times");
    Controller1.Screen.setCursor(4, 1);
    Controller1.Screen.print("Right Joystick pushed ", rightTogglePush); Controller1.Screen.print(" times");

    /*------------------------------------------------------------------------------------------------------------------------*/
    //THIS SECTION DEALS WITH BRAIN SCREEN SETUP
    /*------------------------------------------------------------------------------------------------------------------------*/
    //Make sure that there isn't anything on the screen to start
    Brain.Screen.clearScreen();
    
    //Like the controller, set the first line to the top left corner, with a small top and left buffer
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Battery Remaining: ", batteryPercent); Brain.Screen.print("%");
    //Note that we use setCursor so that we always know that we're going to the proper line each time we write a line
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Drivetrain Velocity: ", drivetrainVelocity);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Drivetrain Current: ", drivetrainCurrent); Brain.Screen.print("%");
    Brain.Screen.setCursor(4, 1);
    //May need to change this to C, docs do not say what unit
    Brain.Screen.print("Drivetrain Temperature: ", drivetrainTemp); Brain.Screen.print("F");
    /*------------------------------------------------------------------------------------------------------------------------*/
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

      //THIS SECTION IS ALL CONTROLLER DISPLAY CONDITIONALS
      /*-------------------------------------------------------------------------------------------------------------------*/
      //This if statement only executes IF the left toggle is pushed up and down.
      if(Controller1.Axis3.position() > 0)
      {
        //We want this variable to tick up each time the toggle is pushed
        leftTogglePush++;
        //Reset the cursor to the proper position
        Controller1.Screen.setCursor(3, 1);
        //Clear the line to prevent oddities in presentation
        Controller1.Screen.clearLine();
        //Reprint the line we printed at the very beginning
        Controller1.Screen.print("Left Joystick pushed ", leftTogglePush); Controller1.Screen.print(" times");
        //This function is the same that we did in tutorial 1. I am explicitly using a different variable simply so that
        //it is clear what the variable's purpose is
        leftTogglePercent = Controller1.Axis3.position(percent);
        //Set cursor to proper position
        Controller1.Screen.setCursor(1, 1);
        //Clear the line
        Controller1.Screen.clearLine();
        //Print
        Controller1.Screen.print("Left Joystick Position: ", leftTogglePercent);
      }
      
      //This if statement does the same thing, except it is for the right toggle being pushed left/right
      if(Controller1.Axis1.position() > 0)
      {
        rightTogglePush++;
        Controller1.Screen.setCursor(4, 1);
        Controller1.Screen.clearLine();
        Controller1.Screen.print("Right Joystick pushed ", rightTogglePush); Controller1.Screen.print(" times");
        rightTogglePercent = Controller1.Axis1.position(percent);
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.clearLine();
        Controller1.Screen.print("Right Joystick Position: ", rightTogglePercent);
      }
      /*-----------------------------------------------------------------------------------------------------------------------*/
      //THIS SECTION DEALS WITH BRAIN DISPLAY CONDITIONALS
      /*-----------------------------------------------------------------------------------------------------------------------*/
      //This doesn't go in a conditional because there isn't really a callback to tell WHEN the battery will tick down like there
      //are for the other functions, like axes
      batteryPercent = Brain.Battery.capacity();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.clearLine();
      Brain.Screen.print("Battery Remaining: ", batteryPercent); Brain.Screen.print("%");

      //Note that this is a much more simplified version of what was done for the controller. This is because we really don't care to
      //update those different values if the drivetrain isn't moving
      if(Drivetrain.isMoving() == true)
      {
        drivetrainVelocity = Drivetrain.velocity(percent);
        drivetrainCurrent = Drivetrain.current();
        drivetrainTemp = Drivetrain.temperature(percent);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Drivetrain velocity: ", drivetrainVelocity);
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Drivetrain current: ", drivetrainCurrent);
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Drivetrain Temperature: ", drivetrainTemp);
      }

    }
}

