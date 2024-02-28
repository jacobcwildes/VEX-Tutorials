#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftRear = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightRear = motor(PORT4, ratio18_1, true);
controller Controller1 = controller(primary);
motor Ratchet = motor(PORT5, ratio36_1, false);
/*vex-vision-config:begin*/
signature Vision4__SIG_1 = signature (1, -6553, -5761, -6158, -5575, -4647, -5110, 2.5, 0);
vision Vision4 = vision (PORT19, 50, Vision4__SIG_1);
/*vex-vision-config:end*/
distance Distance3 = distance(PORT18);
motor Catapult = motor(PORT6, ratio36_1, true);
motor Catapult2 = motor(PORT17, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}