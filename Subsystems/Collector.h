#include <WPILib.h>
#include "../Definitions.h"

class ZaphodCollector
{
  private:
    Jaguar *collectorMotor;
  public:
    ZaphodCollector();
    void collectBall();
    void releaseBall();
    void spinWithShot(float);
};
