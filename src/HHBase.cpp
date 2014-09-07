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
  //Checks the state of the drive joystick to make sure it was not moved
  //while plugged in, giving inaccurate readings
  if(!hHBot->CheckJoystickValues()){
    printf("***UNPLUG AND REPLUG THE JOYSTICKS***\n");
  }
}
//Config testing
std::map<std::string, std::string> options;
void parse(std::ifstream & cfgfile){
  std::string id, eq, val;
  while(cfgfile >> id >> eq >> val){
    if (id[0] == '#') continue;
    if (eq != "=") throw std::runtime_error("Parse error");
    options[id] = val;
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
  hHBot->Handler();
}
void HHBase::Test(){}
START_ROBOT_CLASS(HHBase);
// vim: ts=2:sw=2:et
