#ifndef __ZAPHOD_ROBOT_H__
#define __ZAPHOD_ROBOT_H__
#include <WPILib.h>
#include "HHBase.h"
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
    Talon *right1, *right2, *right3, *left1, *left2, *left3;
    Joystick *rightStick, *leftStick;
    JoystickController *controlSystem;
    NetworkTable *netTable;
    HHShooter *shooter;
    HHCollector *collector;
    HHCompressor *compressorSystem;
    HHDashboard *dashboard;
    HHSonar *sonar;
  public:
    HHRobot();
    bool CheckJoystickValues();
    void Init();
    void DriveRobot(float,float);
    void UpdateDashboard();
    void Handler();
    void RunAuto();
};
#endif
// vim: ts=2:sw=2:et
