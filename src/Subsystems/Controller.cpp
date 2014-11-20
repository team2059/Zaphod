#include "Controller.h"
JoystickController::JoystickController(){
  driveJoystick=new Joystick(JOYSTICK_RIGHT);
  shootJoystick=new Joystick(JOYSTICK_LEFT);
}
void JoystickController::UpdateJoysticks(){
  throttle=(-leftJoystickAxisValues[4]+1)/2;
}
int JoystickController::GetJoystickButton(int joystick, int button){
  switch (joystick){
    case 1:
      return driveJoystick->GetRawButton(button);
      break;
    case 2:
      return shootJoystick->GetRawButton(button);
      break;
    default:
      return -1;
      break;
  }
}
float JoystickController::GetJoystickAxis(int joystick, int axis){
  switch (joystick){
    case 1:
      return driveJoystick->GetRawAxis(axis);
      break;
    case 2:
      return shootJoystick->GetRawAxis(axis);
      break;
    default:
      return 999;
      break;
  }
}
// vim: ts=2:sw=2:et
