#include "Controller.h"
Extreme3dPro::Extreme3dPro(uint8_t port){
  stickofjoy = new Joystick(port);
}
float Extreme3dPro::GetThrottle(){
  return (-GetRawJoystickAxis(4)+1)/2;
}
int Extreme3dPro::GetJoystickButton(uint8_t button){
  return stickofjoy->GetRawButton(button);
}
float Extreme3dPro::GetRawJoystickAxis(uint8_t axis){
  return stickofjoy->GetRawAxis(axis);
}
float Extreme3dPro::GetJoystickAxis(std::string axis){
    if (axis == "x"){
      return stickofjoy->GetX();
    }else if (axis == "y"){
      return stickofjoy->GetY();
    }else if (axis == "z"){
      return stickofjoy->GetZ();
    }else if(axis == "throttle"){
      return stickofjoy->GetRawAxis(4);
    }else{
      return 0;
    }
}
void Extreme3dPro::handler(){
  for(int i=0;i<=11;i++){
    ButtonValue[i] = stickofjoy->GetRawButton(i);
  }
}
// vim: ts=2:sw=2:et
