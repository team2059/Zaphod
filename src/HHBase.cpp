#include "HHBase.h"

HHBase::HHBase():
  hHBot(new HHRobot()){
    printf("Done\n");
  }
void HHBase::RobotInit(){
  //Checks the state of the drive joystick to make sure it was not moved
  //while plugged in, giving inaccurate readings
  if(!hHBot->checkJoystickValues()){
    printf("***UNPLUG AND REPLUG THE JOYSTICKS***\n");
  }
}
void HHBase::DisabledInit(){}
void HHBase::AutonomousInit(){}
void HHBase::TeleopInit(){}
void HHBase::DisabledContinuous(){}
void HHBase::AutonomousContinuous(){}
void HHBase::TeleopContinuous(){}
void HHBase::DisabledPeriodic(){}
void HHBase::AutonomousPeriodic(){}
void HHBase::TeleopPeriodic(){
  hHBot->handler();
}
void HHBase::Test(){}
START_ROBOT_CLASS(HHBase);
