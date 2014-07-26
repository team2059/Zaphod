#include "Collector.h"
HHCollector::HHCollector(){
  collectorMotor = new Jaguar(COLLECTOR_SIDECAR, COLLECTOR_MOTOR);
}
void HHCollector::updateCollector(bool shooting, float angle){
  //Needed for the auto running of collector when shooting
  if(shooting){
    if(angle <= 40){
      collectBall();
    }
  }
  if(e_CollectorState == COLLECTING){
    collectBall();
  }
  if(e_CollectorState == RELEASE){
    releaseBall();
  }
  if(e_CollectorState == STOP){
    collectorMotor->Set(0);
  }
}
void HHCollector::collectBall(){
  collectorMotor->Set(1);
}
void HHCollector::releaseBall(){
  collectorMotor->Set(255);
}
