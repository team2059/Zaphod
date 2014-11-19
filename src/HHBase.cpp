#include "HHBase.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
HHBase::HHBase():
  hHBot(new HHRobot()){
    printf("Done\n");
  }
void HHBase::RobotInit(){
  hHBot->Init();
}
void HHBase::DisabledInit(){}
void HHBase::AutonomousInit(){
  hHBot->Init();
}
void HHBase::TeleopInit(){
  hHBot->Init();
}
void HHBase::DisabledContinuous(){}
void HHBase::AutonomousContinuous(){}
void HHBase::TeleopContinuous(){}
void HHBase::DisabledPeriodic(){}
void HHBase::AutonomousPeriodic(){
  hHBot->RunAuto();
}
void HHBase::TeleopPeriodic(){
  hHBot->Handler();
}
void HHBase::Test(){}
START_ROBOT_CLASS(HHBase);
// vim: ts=2:sw=2:et
