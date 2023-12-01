#include "vex.h"
#include "autonomy.h"

int notSeen = 0; //Track how many times we haven't seen a ball
int seenFirst = 0;

//Turn manipulators for when we are in a close focal distance
int leftAdder = 0;
int rightAdder = 0;
int forwardAdder = 0;

int rangeVal = 20;
int adderVal = 8;
int forwardadderVal = 60;
bool leftRight = false; //Keeps track of which way we should spin based on the last time the ball was seen
void autonomy(imuDat *imuData)
{
    //Vision Sensor logic:

    Vision4.takeSnapshot(Vision4__SIG_1);
    //Is the ball in view?
    if(Vision4.objects[0].exists)
    {
      notSeen = 0;
      seenFirst = 1;
      Brain.Screen.print("Ball detected");
      Brain.Screen.newLine();
      Brain.Screen.print("Ball X: %d", ((int) Vision4.objects[0].centerX));
      Brain.Screen.newLine();
      Brain.Screen.print("Ball Y: %d", ((int) Vision4.objects[0].centerY));
      Brain.Screen.newLine();
      Brain.Screen.print("Distance: %f (in)", Distance3.objectDistance(inches));
      Brain.Screen.setCursor(1, 1);
      //If the ball is too far away
      if(Distance3.objectDistance(inches) > 10) //Change this later after testing
      {

        if((int)Vision4.objects[0].centerX < 120) //Spin left if ball too far left
        {
          leftRight = false;
          Motor10.setVelocity(-3, percent);
          Motor1.setVelocity(3, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);

        }
        else if((int)Vision4.objects[0].centerX > 180) //Spin right if ball too far right
        {
          leftRight = true;
          Motor10.setVelocity(3, percent);
          Motor1.setVelocity(-3, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);

        }
        else
        {
          if((int)Vision4.objects[0].centerX < 150)
          {
            leftAdder = -adderVal;
            rightAdder = adderVal;
          }
          else if((int)Vision4.objects[0].centerX > 150)
          {
            leftAdder = adderVal;
            rightAdder = -adderVal;
          }
          if(((int)Vision4.objects[0].centerX > 150 - rangeVal) && ((int)Vision4.objects[0].centerX < 150 + rangeVal)) forwardAdder = forwardadderVal;
          
          else forwardAdder = 0;

          Motor1.setVelocity(forwardAdder + rightAdder, percent);
          Motor10.setVelocity(forwardAdder + leftAdder, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);
          leftAdder = 0;
          rightAdder = 0;
        }
      }
      else
      {
        Motor6.spinFor(forward, 60, degrees);
        Motor1.setStopping(brake);
        Motor10.setStopping(brake);
        Motor1.stop();
        Motor10.stop();
      }

    }
    else
    {
      if(notSeen > 10)
      {
        if(leftRight == false) //Spin to the left to find the ball
        {
          Motor6.stop();
          Motor1.spin(forward);
          Motor1.setVelocity(20, percent);
          Motor10.spin(forward);
          Motor10.setVelocity(-20, percent);

        }
        if(leftRight == true) //Spin to the right to find the ball
        {
          Motor6.stop();
          Motor1.spin(forward);
          Motor1.setVelocity(-20, percent);
          Motor10.spin(forward);
          Motor10.setVelocity(20, percent);

        }
      }
      notSeen++;
      seenFirst = 0;
    }

}