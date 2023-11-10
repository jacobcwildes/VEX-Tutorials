#include "controller.h"
#include "vex.h"

int controllerUse(ConDat *controllerData) //Function to run the controller only
{
    controllerData->desiredPos = Controller1.Axis3.position(percent); //useless motor
    controllerData->turn = Controller1.Axis1.position(percent); //left/right
    controllerData->forw = (int) Controller1.ButtonR1.pressing();
    controllerData->back = (int) Controller1.ButtonR2.pressing();

    controllerData->debugDrive = ((controllerData->forw * 50) - (controllerData->back * 50) + (controllerData->turn * .4));

    controllerData->left = ((controllerData->forw * 50) - (controllerData->back * 50) + (controllerData->turn * .4));
    controllerData->right = ((controllerData->forw * 50) - (controllerData->back * 50) - (controllerData->turn * .4));

    if(controllerData->turn == 0)
    {
      controllerData->left *= 2;
      controllerData->right *= 2;
    }

    if(abs((int) (left)) > abs((int) (right)))
    {
      controllerData->divisor = controllerData->left;
    }
    else
    { 
      controllerData->divisor = controllerData->right;
    }
      //controllerData->left *= 100.0;
      //controllerData->left /= abs((int) controllerData->divisor);
      //controllerData->right *= 100.0;
      //controllerData->right /= abs((int) controllerData->divisor);
      Motor10.spin(forward);
      Motor10.setVelocity((int)controllerData->left, percent);
      Motor1.spin(forward);
      Motor1.setVelocity((int)controllerData->right, percent);
      Motor6.spinToPosition(((int) ((float) controllerData->desiredPos * 3.6)), degrees, false);
    return 1;
}