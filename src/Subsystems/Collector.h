#include <WPILib.h>
#include "../Definitions.h"
class ZaphodCollector
{
  private:
    Jaguar *collectorMotor;
  public:
    enum{
      COLLECTING,
      RELEASE,
      STOP
    }e_CollectorState;
    ZaphodCollector();
    void updateCollector(bool, float);
    void collectBall();
    void releaseBall();
    void spinWithShot(float);
};
