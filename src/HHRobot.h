#ifndef __ZAPHOD_ROBOT_H__
#define __ZAPHOD_ROBOT_H__
#include <WPILib.h>
#include "HHBase.h"
#include "Auto/AutoMain.h"
#include "Definitions.h"
class JoystickController;
class HHShooter;
class HHCollector;
class HHCompressor;
class HHDashboard;
class HHRobot;
class HHSonar;
class HHRobot{
  private:
    Jaguar *right1, *right2, *right3, *left1, *left2, *left3;
    JoystickController *ControlSystem;
    NetworkTable *netTable;
    HHShooter *shooter;
    HHCollector *collector;
    HHCompressor *compressorSystem;
    HHDashboard *dashboard;
    HHAuto *autoseq;
    HHSonar *sonar;
  public:
    HHRobot();
    bool CheckJoystickValues();
    void DriveRobot(float,float);
    void UpdateDashboard();
    void Handler();
    void RunAuto();
};
#endif
// vim: ts=2:sw=2:et
