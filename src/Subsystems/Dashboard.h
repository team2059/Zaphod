#include "SmartDashboard/SmartDashboard.h"
#include <WPILib.h>
#include "../Definitions.h"
class ZaphodDashboard
{
  public:
    ZaphodDashboard();
    //Array used to track the values in the dashboard
    bool DashboardValues[];
    float getKeyValue(const char* key);
    bool putKeyValue(const char* key, float value);
};
