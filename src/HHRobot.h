#ifndef __ZAPHOD_ROBOT_H__
#define __ZAPHOD_ROBOT_H__
#include <WPILib.h>
#include "HHBase.h"
#include "lib/drive/WCDrive.h"
#include "lib/controller/Controller.h"
#include "Definitions.h"
class HHShooter;
class HHCollector;
class HHCompressor;
class HHDashboard;
class HHRobot;
class HHSonar;
class HHRobot{
  private:
    WCDrive *drive;
    Extreme3dPro *driveStick, *shootStick;
    NetworkTable *driveTable, *shooterTable, *collectorTable;
    HHShooter *shooter;
    HHCollector *collector;
    HHCompressor *compressorSystem;
    HHDashboard *dashboard;
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
