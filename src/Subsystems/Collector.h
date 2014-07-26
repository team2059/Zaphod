#include <WPILib.h>
#include "../Definitions.h"
class HHCollector{
  private:
    Jaguar *collectorMotor;
  public:
    enum{
      COLLECTING,
      RELEASE,
      STOP
    }e_CollectorState;
    HHCollector();
    void updateCollector(bool, float);
    void collectBall();
    void releaseBall();
    void spinWithShot(float);
};
