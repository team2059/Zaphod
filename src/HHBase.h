#ifndef __HH_BASE_H__
#define __HH_BASE_H__
#include <WPILib.h>
#include "ZaphodRobot.h"
#include "Subsystems/Controller.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Collector.h"
#include "Subsystems/Compressor.h"
#include "Subsystems/Dashboard.h"
//Because this is the first header to be included, classes need to be declared here
class ZaphodRobot;
class HHShooter;
class HHCollector;
class HHCompressor;
class JoystickController;
class HHBase : public IterativeRobot{
  private:
    ZaphodRobot* hHBot;
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
