#include <WPILib.h>
#include "../Definitions.h"

class JoystickController
{
  private:
    Joystick *rightJoystick, *leftJoystick;
  public:
    int leftJoystickValues[];
    int rightJoystickValues[];
    JoystickController();
    void getRightJoystick();
    void getLeftJoystick();
};
