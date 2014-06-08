#include "Dashboard.h"

ZaphodDashboard::ZaphodDashboard()
{
}

float ZaphodDashboard::getKeyValue(const char* key)
{
  return 1.0f;
}

bool ZaphodDashboard::putKeyValue(const char* key, float value)
{
  SmartDashboard::PutNumber(key,value);
  return true;
}
