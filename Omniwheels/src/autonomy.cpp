#include "vex.h"
#include "autonomy.h"

int notSeen = 0; //Track how many times we haven't seen a ball
int seenFirst = 0;

int catapultDown = 0; //Track how many times we have lowered the catapult

//Turn manipulators for when we are in a close focal distance
int leftAdder = 0;
int rightAdder = 0;
int forwardAdder = 0;

int rangeVal = 20;
int adderVal = 8;
int forwardadderVal = 60;
bool leftRight = false; //Keeps track of which way we should spin based on the last time the ball was seen
void autonomy(void)
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
          LeftFront.setVelocity(-3, percent);
          LeftRear.setVelocity(-3, percent);
          RightFront.setVelocity(3, percent);
          RightRear.setVelocity(3, percent);
          RightFront.spin(forward);
          RightRear.spin(forward);
          LeftFront.spin(forward);
          LeftRear.spin(forward);

        }
        else if((int)Vision4.objects[0].centerX > 180) //Spin right if ball too far right
        {
          leftRight = true;
          LeftFront.setVelocity(3, percent);
          LeftRear.setVelocity(3, percent);
          RightFront.setVelocity(-3, percent);
          RightRear.setVelocity(-3, percent);
          RightFront.spin(forward);
          RightRear.spin(forward);
          LeftFront.spin(forward);
          LeftRear.spin(forward);

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

          RightFront.setVelocity(forwardAdder + rightAdder, percent);
          LeftFront.setVelocity(forwardAdder + leftAdder, percent);
          RightFront.spin(forward);
          LeftFront.spin(forward);
          leftAdder = 0;
          rightAdder = 0;
        }
      }
      else
      {
        //Do something when we reach the ball
        if(catapultDown == 0)
        {
          Catapult.spinToPosition((Catapult.position(degrees) - 100), degrees);
          catapultDown = 1;
        }
        
        RightFront.setStopping(brake);
        RightRear.setStopping(brake);
        LeftFront.setStopping(brake);
        LeftRear.setStopping(brake);
        RightFront.stop();
        RightRear.stop();
        LeftFront.stop();
        LeftRear.stop();
      }

    }
    else
    {
      if(notSeen > 10)
      {
        if(leftRight == false) //Spin to the left to find the ball
        {
          //Have not found ball, stop whatever we were doing
          RightFront.spin(forward);
          RightRear.spin(forward);
          RightFront.setVelocity(20, percent);
          RightRear.setVelocity(20, percent);
          LeftFront.spin(forward);
          LeftRear.spin(forward);
          LeftFront.setVelocity(-20, percent);
          LeftRear.setVelocity(-20, percent);

        }
        if(leftRight == true) //Spin to the right to find the ball
        {
          //Have not found the ball, stop whatever we were doing
          RightFront.spin(forward);
          RightRear.spin(forward);
          RightFront.setVelocity(-20, percent);
          RightRear.setVelocity(-20, percent);
          LeftFront.spin(forward);
          LeftRear.spin(forward);
          LeftFront.setVelocity(20, percent);
          LeftRear.setVelocity(20, percent);

        }
      }
      notSeen++;
      seenFirst = 0;
    }

}