#include "SmartDashboard/SmartDashboard.h"
#include <WPILib.h>
#include "../Definitions.h"
class HHDashboard{
  public:
    HHDashboard();
    //Array used to track the values in the dashboard
    bool DashboardValues[];
    float getFloatValue(const char* key);
    bool putFloatValue(const char* key, float value);
    bool getBoolValue(const char* key);
    bool putBoolValue(const char* key, bool value);
};
