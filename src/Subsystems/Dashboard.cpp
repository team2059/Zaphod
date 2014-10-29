#include "Dashboard.h"
HHDashboard::HHDashboard(){
}
float HHDashboard::GetFloatValue(const char* key){
  float value=SmartDashboard::GetNumber(key);
  return value;
}
bool HHDashboard::PutFloatValue(const char* key, float value){
  SmartDashboard::PutNumber(key,value);
  return true;
}
bool HHDashboard::GetBoolValue(const char* key){
  bool value=SmartDashboard::GetBoolean(key);
  return value;
}
bool HHDashboard::PutBoolValue(const char* key, bool value){
  SmartDashboard::PutBoolean(key,value);
  return true;
}
// vim: ts=2:sw=2:et
