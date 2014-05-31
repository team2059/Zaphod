#include "Collector.h"

ZaphodCollector::ZaphodCollector()
{
  collectorMotor = new Jaguar(COLLECTOR_SIDECAR, COLLECTOR_MOTOR);
}

void ZaphodCollector::updateCollector(bool shooting, float angle)
{
  //Needed for the auto running of collector when shooting
  if(shooting)
  {
    if(angle <= 40)
    {
      collectBall();
    }
  }
  //
  if(e_CollectorState == COLLECTING)
  {
    collectBall();
  }
  if(e_CollectorState == RELEASE)
  {
    releaseBall();
  }
  if(e_CollectorState == STOP)
  {
    collectorMotor->Set(0);
  }
}

void ZaphodCollector::collectBall()
{
  collectorMotor->Set(1);
}

void ZaphodCollector::releaseBall()
{
  collectorMotor->Set(255);
}
