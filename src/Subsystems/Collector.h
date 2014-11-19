#include <WPILib.h>
#include "../Definitions.h"
class HHCollector{
  private:
    Talon *collectorMotor;
  public:
    HHCollector();
    enum{
      COLLECTING,
      RELEASE,
      STOP
    }e_CollectorState;
    void UpdateCollector(bool, float);
    void CollectBallAtSpeed(float speed);
    void CollectorStop();
    void CollectBall();
    void ReleaseBall();
    void SpinWithShot(float);
};
// vim: ts=2:sw=2:et
