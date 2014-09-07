#include <WPILib.h>
#include "../Definitions.h"
class HHCollector{
  private:
    Jaguar *collectorMotor;
  public:
    HHCollector();
    enum{
      COLLECTING,
      RELEASE,
      STOP
    }e_CollectorState;
    void UpdateCollector(bool, float);
    void CollectBall();
    void ReleaseBall();
    void SpinWithShot(float);
};
// vim: ts=2:sw=2:et
