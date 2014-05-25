#include "Controller.h"

JoystickController::JoystickController()
{
  rightJoystick = new Joystick(JOYSTICK_RIGHT);
  leftJoystick = new Joystick(JOYSTICK_LEFT);
}

void JoystickController::updateJoysticks()
{
  getRightJoystick();
  getLeftJoystick();
  getRightJoystickAxis();
  getLeftJoystickAxis();
  throttle = (-leftJoystickAxisValues[4]+1)/2;
}

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

void JoystickController::getRightJoystickAxis()
{
  for(int i=1; i<7; i++)
  {
    rightJoystickAxisValues[i] = rightJoystick->GetRawAxis(i);
  }
}

void JoystickController::getLeftJoystickAxis()
{
  for(int i=1; i<7; i++)
  {
    leftJoystickAxisValues[i] = leftJoystick->GetRawAxis(i);
  }
}
