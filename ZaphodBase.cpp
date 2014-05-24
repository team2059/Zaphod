#include "ZaphodBase.h"

ZaphodBase::ZaphodBase():
  zBot(new ZaphodRobot())
{
  printf("Done.\n");
}
void ZaphodBase::RobotInit()
{
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
START_ROBOT_CLASS(ZaphodBase);
