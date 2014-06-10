#include "Dashboard.h"

ZaphodDashboard::ZaphodDashboard()
{
  //Add Dashboard Initalizations here (for now)
  SmartDashboard::PutNumber("Shooting Power", 0.0f);
  SmartDashboard::PutBoolean("Joysticks Valid", false);
}

float ZaphodDashboard::getFloatValue(const char* key)
{
  float value = SmartDashboard::GetNumber(key);
  return value;
}

bool ZaphodDashboard::putFloatValue(const char* key, float value)
{
  SmartDashboard::PutNumber(key,value);
  return true;
}

bool ZaphodDashboard::getBoolValue(const char* key)
{
  bool value = SmartDashboard::GetBoolean(key);
  return value;
}

bool ZaphodDashboard::putBoolValue(const char* key, bool value)
{
  SmartDashboard::PutBoolean(key,value);
  return true;
}
