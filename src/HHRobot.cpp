#include "HHRobot.h"
#include "HHBase.h"
HHRobot::HHRobot():
  ControlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()),
  sonar(new HHSonar()){
    //comment
  }
//Functions to get sonar values and return as INCH values
bool HHRobot::checkJoystickValues(){
  float x=ControlSystem->rightJoystickAxisValues[1];
  float y=ControlSystem->rightJoystickAxisValues[2];
  if((-.1 < x && x < .1) && (-.1 < y && y < .1)) {
    dashboard->putBoolValue("Joysticks Valid", true);
    return true;
  } else {
    dashboard->putBoolValue("Joysticks Valid", false);
    return true;
    return false;
  }
}
void HHRobot::driveRobot(float x, float y){
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
void HHRobot::updateDashboard(){
  dashboard->putFloatValue("Shooting Power", ControlSystem->throttle);
}
//Main function used to handle periodic tasks on the robot
void HHRobot::handler(){
  //Periodic tasks that should be run by every loop
  ControlSystem->updateJoysticks();
  shooter->updateShooterPosition();
  //TODO Need to implement a timing system to not break the spike (this function doesn't run the compressor at the moment)
  compressorSystem->compressorSystemPeriodic();
  collector->updateCollector(shooter->isShooting, shooter->getAngle());
  if(checkJoystickValues()) {
    driveRobot(ControlSystem->rightJoystickAxisValues[3]+ControlSystem->rightJoystickAxisValues[1], -ControlSystem->rightJoystickAxisValues[2]);
  }
  updateDashboard();
  //Button assignments to actions
  if(ControlSystem->leftJoystickValues[SHOOTER_FIRE]) {
    shooter->startShootingSequence(ControlSystem->throttle);
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_INTAKE]) {
    collector->collectBall();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_OUTTAKE]) {
    collector->releaseBall();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_EXTEND]) {
    compressorSystem->extendCollector();
  }
  if(ControlSystem->rightJoystickValues[COLLECTOR_RETRACT]) {
    compressorSystem->retractCollector();
  }
}
