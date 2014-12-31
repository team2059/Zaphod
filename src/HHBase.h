#ifndef __HH_BASE_H__
#define __HH_BASE_H__
#include <WPILib.h>
#include "HHRobot.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Collector.h"
#include "Subsystems/Sonar.h"
#include <string>
//Because this is the first header to be included, classes need to be declared here
class HHRobot;
class HHShooter;
class HHCollector;
class HHSonar;
class HHBase : public IterativeRobot{
  private:
    HHRobot* hHBot;
  public:
    HHBase();
    void RobotInit();
    void DisabledInit();
    void AutonomousInit();
    void TeleopInit();
    void DisabledContinuous();
    void AutonomousContinuous();
    void TeleopContinuous();
    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();
    void Test();
};
#endif
// vim: ts=2:sw=2:et
