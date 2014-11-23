#include <WPILib.h>
#include "../Definitions.h"
class JoystickController
{
  private:
    Joystick *driveJoystick, *shootJoystick;
  public:
    JoystickController();
    float GetThrottle();
    int GetJoystickButton(int,int);
    float GetRawJoystickAxis(int,int);
    float GetJoystickAxis(int, std::string axis);
};
// vim: ts=2:sw=2:et
