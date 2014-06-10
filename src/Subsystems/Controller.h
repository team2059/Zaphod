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
    void updateJoysticks();
    void getRightJoystick();
    void getLeftJoystick();
    void getLeftJoystickAxis();
    void getRightJoystickAxis();
};
