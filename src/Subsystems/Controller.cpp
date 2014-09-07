#include "Controller.h"
JoystickController::JoystickController(){
  rightJoystick=new Joystick(JOYSTICK_RIGHT);
  leftJoystick=new Joystick(JOYSTICK_LEFT);
}
void JoystickController::UpdateJoysticks(){
  GetRightJoystick();
  GetLeftJoystick();
  GetRightJoystickAxis();
  GetLeftJoystickAxis();
  throttle=(-leftJoystickAxisValues[4]+1)/2;
}
void JoystickController::GetRightJoystick(){
  for(int i=1;i<13;i++){
    rightJoystickValues[i]=rightJoystick->GetRawButton(i);
  }
}
void JoystickController::GetLeftJoystick(){
  for(int i=1;i<13;i++){
    leftJoystickValues[i]=leftJoystick->GetRawButton(i);
  }
}
void JoystickController::GetRightJoystickAxis(){
  for(int i=1;i<7;i++){
    rightJoystickAxisValues[i]=rightJoystick->GetRawAxis(i);
  }
}
void JoystickController::GetLeftJoystickAxis(){
  for(int i=1;i<7;i++){
    leftJoystickAxisValues[i]=leftJoystick->GetRawAxis(i);
  }
}
// vim: ts=2:sw=2:et
