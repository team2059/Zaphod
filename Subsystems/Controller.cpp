#include "Controller.h"

JoystickController::JoystickController()
{
  rightJoystick = new Joystick(JOYSTICK_RIGHT);
  leftJoystick = new Joystick(JOYSTICK_LEFT);
}

//void JoystickController::getRightJoystick(JoystickController *controller)
void JoystickController::getRightJoystick()
{
  for(int i=1; i<13; i++)
  {
    rightJoystickValues[i] = rightJoystick->GetRawButton(i);
  }
}

void JoystickController::getLeftJoystick()
{
  for(int i=1; i<13; i++)
  {
    leftJoystickValues[i] = leftJoystick->GetRawButton(i);
  }
}
