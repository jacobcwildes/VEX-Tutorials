#include "vex.h"

int notSeen = 0; //Track how many times we haven't seen a ball
int seenFirst = 0;
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
          Motor10.setVelocity(-3, percent);
          Motor1.setVelocity(3, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);

        }
        else if((int)Vision4.objects[0].centerX > 180) //Spin right if ball too far right
        {
          Motor10.setVelocity(3, percent);
          Motor1.setVelocity(-3, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);

        }
        else
        {
          Motor1.setVelocity(20, percent);
          Motor10.setVelocity(20, percent);
          Motor1.spin(forward);
          Motor10.spin(forward);
        }
      }
      else
      {
        Motor6.spinFor(forward, 60, degrees);
        Motor1.stop();
        Motor10.stop();
      }

    }
    else
    {
      if(notSeen > 10)
      {
        Motor6.stop();
        Motor1.spin(forward);
        Motor1.setVelocity(30, percent);
        Motor10.spin(forward);
        Motor10.setVelocity(-30, percent);
      }
      notSeen++;
      seenFirst = 0;
    }

}