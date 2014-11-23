#include "Controller.h"
JoystickController::JoystickController(){
  driveJoystick=new Joystick(JOYSTICK_RIGHT);
  shootJoystick=new Joystick(JOYSTICK_LEFT);
}
float JoystickController::GetThrottle(){
  return (-GetRawJoystickAxis(2,4)+1)/2;
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
float JoystickController::GetRawJoystickAxis(int joystick, int axis){
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

float JoystickController::GetJoystickAxis(int joystick, std::string axis){
  if (joystick == 1) {
    if (axis == "x"){
      return driveJoystick->GetX();
    }else if (axis == "y"){
      return driveJoystick->GetY();
    }else if (axis == "z"){
      return driveJoystick->GetZ();
    }else{
      return 0;
    }
  }else{
    return 0;
  }
}
// vim: ts=2:sw=2:et
