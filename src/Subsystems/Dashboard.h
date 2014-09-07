#include "SmartDashboard/SmartDashboard.h"
#include <WPILib.h>
#include "../Definitions.h"
class HHDashboard{
  public:
    HHDashboard();
    //Array used to track the values in the dashboard
    bool DashboardValues[];
    float GetFloatValue(const char* key);
    bool PutFloatValue(const char* key, float value);
    bool GetBoolValue(const char* key);
    bool PutBoolValue(const char* key, bool value);
};
// vim: ts=2:sw=2:et
