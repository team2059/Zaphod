#include <WPILib.h>
#include "../Definitions.h"
// Logitech Extreme 3D Pro joysticks
class Extreme3dPro
{
  private:
    Joystick *stickofjoy;
  public:
    //Array to hold joystick button values
    int ButtonValue[11];
    //Call periodically to update joystick values
    void handler();
    Extreme3dPro(uint8_t);
    float GetThrottle();
    int GetJoystickButton(uint8_t);
    float GetRawJoystickAxis(uint8_t);
    float GetJoystickAxis(std::string axis);
};
// vim: ts=2:sw=2:et
