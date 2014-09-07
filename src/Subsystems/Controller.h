#include <WPILib.h>
#include "../Definitions.h"
class JoystickController
{
  private:
    Joystick *rightJoystick, *leftJoystick;
  public:
    int leftJoystickValues[];
    int rightJoystickValues[];
    float leftJoystickAxisValues[];
    float rightJoystickAxisValues[];
    float throttle;
    JoystickController();
    void UpdateJoysticks();
    void GetRightJoystick();
    void GetLeftJoystick();
    void GetLeftJoystickAxis();
    void GetRightJoystickAxis();
};
// vim: ts=2:sw=2:et
