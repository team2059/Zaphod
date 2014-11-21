#include "Controller.h"
JoystickController::JoystickController(){
  driveJoystick=new Joystick(JOYSTICK_RIGHT);
  shootJoystick=new Joystick(JOYSTICK_LEFT);
}
float JoystickController::GetThrottle(){
  return (-GetJoystickAxis(2,4)+1)/2;
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
      printf("Button from joystick %d does not exist!\n", joystick);
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
      printf("Axis from joystick %d does not exist!\n", joystick);
      return 999;
      break;
  }
}
// vim: ts=2:sw=2:et
