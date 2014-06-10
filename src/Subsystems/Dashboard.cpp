#include "Dashboard.h"

ZaphodDashboard::ZaphodDashboard()
{
  //Add Dashboard Initalizations here (for now)
  SmartDashboard::PutNumber("Shooting Power", 0.0f);
}

float ZaphodDashboard::getKeyValue(const char* key)
{
  float value = SmartDashboard::GetNumber(key);
  return value;
}

bool ZaphodDashboard::putKeyValue(const char* key, float value)
{
  SmartDashboard::PutNumber(key,value);
  return true;
}
