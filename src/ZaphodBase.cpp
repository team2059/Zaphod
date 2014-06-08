#include "ZaphodBase.h"

ZaphodBase::ZaphodBase():
  zBot(new ZaphodRobot())
{
  printf("Done.\n");
}
void ZaphodBase::RobotInit()
{
  //Checks the state of the drive joystick to make sure it was not moved
  //while plugged in, giving inaccurate readings
  if(!zBot->checkJoystickValues())
  {
    printf("***UNPLUG AND REPLUG THE JOYSTICKS***\n"); 
  }
}
void ZaphodBase::DisabledInit()
{
}
void ZaphodBase::AutonomousInit()
{
}
void ZaphodBase::TeleopInit()
{
}
void ZaphodBase::DisabledContinuous()
{
}
void ZaphodBase::AutonomousContinuous()
{
}
void ZaphodBase::TeleopContinuous()
{
}
void ZaphodBase::DisabledPeriodic()
{
}
void ZaphodBase::AutonomousPeriodic()
{
}
void ZaphodBase::TeleopPeriodic()
{
  zBot->handler();
}
void ZaphodBase::Test()
{
}
START_ROBOT_CLASS(ZaphodBase);
