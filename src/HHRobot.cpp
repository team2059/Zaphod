#include "HHRobot.h"
#include "HHBase.h"
HHRobot::HHRobot():
  ControlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()),
  sonar(new HHSonar()){
  }
bool HHRobot::CheckJoystickValues(){
  float x=ControlSystem->rightJoystickAxisValues[1];
  float y=ControlSystem->rightJoystickAxisValues[2];
  if((-.1 < x && x < .1) && (-.1 < y && y < .1)) {
    dashboard->PutBoolValue("Joysticks Valid", true);
    return true;
  } else {
    dashboard->PutBoolValue("Joysticks Valid", false);
    return true;
    return false;
  }
}
void HHRobot::DriveRobot(float x, float y){
  if(y>1.0f) {
    y=1.0f;
  } else if(y!=0.0f&&y<-1.0f) {
    y=-1.0f;
  }
  float leftPower=((y+x)/2+1)*127+1;
  float rightPower=((y-x)/2+1)*127+1;
  right1->SetRaw(int(rightPower));
  right2->SetRaw(int(rightPower));
  right3->SetRaw(int(rightPower));
  left1->SetRaw(int(leftPower));
  left2->SetRaw(int(leftPower));
  left3->SetRaw(int(leftPower));
}
void HHRobot::UpdateDashboard(){
  dashboard->PutFloatValue("Shooting Power", ControlSystem->throttle);
}
//Main function used to handle periodic tasks on the robot
void HHRobot::Handler(){
  //Periodic tasks that should be run by every loop
  ControlSystem->UpdateJoysticks();
  shooter->UpdateShooterPosition();
  //TODO Need to implement a timing system to not break the spike (this function doesn't run the compressor at the moment)
  compressorSystem->CompressorSystemPeriodic();
  collector->UpdateCollector(shooter->isShooting, shooter->GetAngle());
  if(CheckJoystickValues()) {
    DriveRobot(ControlSystem->rightJoystickAxisValues[3]+ControlSystem->rightJoystickAxisValues[1], -ControlSystem->rightJoystickAxisValues[2]);
  }
  UpdateDashboard();
  //Button assignments to actions
  if(ControlSystem->leftJoystickValues[SHOOTER_FIRE]) {
    shooter->StartShootingSequence(ControlSystem->throttle);
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_INTAKE]) {
    collector->CollectBall();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_OUTTAKE]) {
    collector->ReleaseBall();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_EXTEND]) {
    compressorSystem->ExtendCollector();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_RETRACT]) {
    compressorSystem->RetractCollector();
  }
}
