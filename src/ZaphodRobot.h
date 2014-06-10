#ifndef __ZAPHOD_ROBOT_H__
#define __ZAPHOD_ROBOT_H__

#include <WPILib.h>
#include "ZaphodBase.h"
#include "Definitions.h"

class JoystickController;
class ZaphodShooter;
class ZaphodCollector;
class ZaphodCompressor;
class ZaphodDashboard;
class ZaphodRobot;

class ZaphodRobot
{
  private:
    Jaguar *right1, *right2, *right3, *left1, *left2, *left3;
    DigitalOutput *frontSonarLeftD, *frontSonarRightD, *rearSonarLeftD, *rearSonarRightD;
    AnalogChannel *frontSonarLeftA, *frontSonarRightA, *rearSonarLeftA, *rearSonarRightA;
    JoystickController *ControlSystem;
    ZaphodShooter *shooter;
    ZaphodCollector *collector;
    ZaphodCompressor *compressorSystem;
    ZaphodDashboard *dashboard;
  public:
    ZaphodRobot();
    float frontSonarLeftV, frontSonarRightV, rearSonarLeftV, rearSonarRightV;
    float getFrontSonar();
    float getRearSonar();
    bool checkJoystickValues();
    void driveRobot(float,float);
    void updateDashboard();
    void handler();
};
#endif
