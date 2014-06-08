#include "SmartDashboard/SmartDashboard.h"
#include <WPILib.h>
#include "../Definitions.h"
class ZaphodDashboard
{
  public:
    ZaphodDashboard();
    float getKeyValue(const char* key);
};
