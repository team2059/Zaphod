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
class HHSonar;
class HHRobot;
class HHRobot{
  private:
    Jaguar *right1, *right2, *right3, *left1, *left2, *left3;
    DigitalOutput *frontSonarLeftD, *frontSonarRightD, *rearSonarLeftD, *rearSonarRightD;
    AnalogChannel *frontSonarLeftA, *frontSonarRightA, *rearSonarLeftA, *rearSonarRightA;
    JoystickController *ControlSystem;
    HHShooter *shooter;
    HHCollector *collector;
    HHCompressor *compressorSystem;
    HHDashboard *dashboard;
    HHSonar *sonar;
  public:
    HHRobot();
    float frontSonarLeftV, frontSonarRightV, rearSonarLeftV, rearSonarRightV;
    bool CheckJoystickValues();
    void DriveRobot(float,float);
    void UpdateDashboard();
    void Handler();
};
#endif
