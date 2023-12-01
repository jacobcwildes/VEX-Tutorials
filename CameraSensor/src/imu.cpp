#include "vex.h"
#include "imu.h"

void reportIMU(imuDat *imuData)
{
 imuData->rotate = Inertial16.rotation(degrees);
 imuData->accel = Inertial16.acceleration(xaxis);
 imuData->head = Inertial16.heading(degrees);
 imuData->orient = Inertial16.orientation(pitch, degrees);
}