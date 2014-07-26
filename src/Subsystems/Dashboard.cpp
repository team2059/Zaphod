#include "Dashboard.h"
HHDashboard::HHDashboard(){
  //Add Dashboard Initalizations here (for now)
  SmartDashboard::PutNumber("Shooting Power", 0.0f);
  SmartDashboard::PutBoolean("Joysticks Valid", false);
}
float HHDashboard::getFloatValue(const char* key){
  float value=SmartDashboard::GetNumber(key);
  return value;
}
bool HHDashboard::putFloatValue(const char* key, float value){
  SmartDashboard::PutNumber(key,value);
  return true;
}
bool HHDashboard::getBoolValue(const char* key){
  bool value=SmartDashboard::GetBoolean(key);
  return value;
}
bool HHDashboard::putBoolValue(const char* key, bool value){
  SmartDashboard::PutBoolean(key,value);
  return true;
}
