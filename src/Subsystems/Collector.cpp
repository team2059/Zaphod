#include "Collector.h"
HHCollector::HHCollector(){
  collectorMotor = new Talon(COLLECTOR_SIDECAR, COLLECTOR_MOTOR);
}
void HHCollector::UpdateCollector(bool shooting, float angle){
  //Needed for the auto running of collector when shooting
  if(shooting){
    if(angle <= 40){
      CollectBall();
    }
  }
  if(e_CollectorState == COLLECTING){
    CollectBall();
  }
  if(e_CollectorState == RELEASE){
    ReleaseBall();
  }
  if(e_CollectorState == STOP){
    collectorMotor->Set(0);
  }
}

void HHCollector::CollectorStop(){
  collectorMotor->Set(0);
}
void HHCollector::CollectBallAtSpeed(float speed){
  collectorMotor->Set(speed);
}
void HHCollector::CollectBall(){
  collectorMotor->Set(-1);
}
void HHCollector::ReleaseBall(){
  collectorMotor->Set(1);
}
// vim: ts=2:sw=2:et
