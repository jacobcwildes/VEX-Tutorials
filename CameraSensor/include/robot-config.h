using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision4__SIG_1;
extern signature Vision4__SIG_2;
extern signature Vision4__SIG_3;
extern signature Vision4__SIG_4;
extern signature Vision4__SIG_5;
extern signature Vision4__SIG_6;
extern signature Vision4__SIG_7;
extern vision Vision4;
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor Motor1;
extern motor Motor10;
extern motor Motor6;
extern distance Distance3;
extern gps GPS16;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );