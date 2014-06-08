#ifndef __ZAPHOD_BASE_H__
#define __ZAPHOD_BASE_H__

#include <WPILib.h>
#include "ZaphodRobot.h"
#include "Subsystems/Controller.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Collector.h"
#include "Subsystems/Compressor.h"
#include "Subsystems/Dashboard.h"

//Because this is the first header to be compiled, classes need to be declared here
class ZaphodRobot;
class ZaphodShooter;
class ZaphodCollector;
class ZaphodCompressor;
class JoystickController;

class ZaphodBase : public IterativeRobot
{
  private:
    ZaphodRobot* zBot;
  public:
    ZaphodBase();
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
