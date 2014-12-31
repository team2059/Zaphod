#ifndef __ZAPHOD_ROBOT_H__
#define __ZAPHOD_ROBOT_H__
#include <WPILib.h>
#include "HHBase.h"
#include "lib/drive/WCDrive.h"
#include "lib/input/controller/Joystick.h"
#include "lib/input/dashboard/SmartDash.h"
#include "lib/pneumatics/Compressor.h"
#include "Definitions.h"
class HHShooter;
class HHCollector;
class HHRobot;
class HHSonar;
class HHRobot{
  private:
    WCDrive *drive;
    Extreme3dPro *driveStick, *shootStick;
    AirCompressor *compressor;
    NetworkTable *driveTable, *shooterTable, *collectorTable;
    HHShooter *shooter;
    HHCollector *collector;
    SmartDash *dashboard;
    HHSonar *sonar;
    Timer *timer;
    double lastTime;
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
