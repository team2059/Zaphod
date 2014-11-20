#include <WPILib.h>
#include "../Definitions.h"
class JoystickController
{
  private:
    Joystick *driveJoystick, *shootJoystick;
  public:
    int leftJoystickValues[];
    int rightJoystickValues[];
    float leftJoystickAxisValues[];
    float rightJoystickAxisValues[];
    float throttle;
    JoystickController();
    void UpdateJoysticks();
    int GetJoystickButton(int,int);
    float GetJoystickAxis(int,int);
};
// vim: ts=2:sw=2:et
