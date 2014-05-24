#include "Collector.h"

ZaphodCollector::ZaphodCollector()
{
  collectorMotor = new Jaguar(COLLECTOR_SIDECAR, COLLECTOR_MOTOR);
}

void ZaphodCollector::collectBall()
{
}

void ZaphodCollector::releaseBall()
{
}

void ZaphodCollector::spinWithShot(float angle)
{
  if(angle <= 80)
  {
    collectorMotor->Set(1);
  }
}
