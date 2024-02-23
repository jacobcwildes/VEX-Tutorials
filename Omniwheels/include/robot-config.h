using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor LeftFront;
extern motor LeftRear;
extern motor RightFront;
extern motor RightRear;
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor Ratchet;
extern signature Vision4__SIG_1;
extern signature Vision4__SIG_2;
extern signature Vision4__SIG_3;
extern signature Vision4__SIG_4;
extern signature Vision4__SIG_5;
extern signature Vision4__SIG_6;
extern signature Vision4__SIG_7;
extern vision Vision4;
extern distance Distance3;
extern motor Catapult;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );