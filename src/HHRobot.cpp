#include "HHRobot.h"
#include "HHBase.h"
HHRobot::HHRobot():
  ControlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()),
  autoseq(new HHAuto()),
  sonar(new HHSonar()){
  }
bool HHRobot::CheckJoystickValues(){
  float x=ControlSystem->rightJoystickAxisValues[1];
  float y=ControlSystem->rightJoystickAxisValues[2];
  if((-.1 < x && x < .1) && (-.1 < y && y < .1)) {
    dashboard->PutBoolValue("Joysticks Valid", true);
    return true;
  }else{
    dashboard->PutBoolValue("Joysticks Valid", false);
    return false;
  }
}
void HHRobot::DriveRobot(float x, float y){
  if(y>1.0f){
    y=1.0f;
  }else if(y!=0.0f&&y<-1.0f){
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
void HHRobot::RunAuto(){
  int step, time;
  compressorSystem->ExtendCollector();
  //TODO I have no idea what rate this loop runs at so we are going to have to fine tune the times
  //Drive for 51 inches/cm/units (or time)
  if(step == 0 && time < 200){
    if(sonar->GetInches("FRONTLEFT") >= 51){
      DriveRobot(0,-.5);
    }else{
      DriveRobot(0,0);
    }
  }else{
    step = 1;
  }
  //TODO Pass the shooting power and sonar distance as variables to the RunAuto function
  //Shoot at a power
  if(step == 1){
    shooter->StartShootingSequence(0.78);
  }else{
    step = 2;
  }
  if(step == 2){
    return;
  }
}

//Main function used to handle periodic tasks on the robot
void HHRobot::Handler(){
  int targetAngle;
  bool allowCompressing = true;
  //Periodic tasks that should be run by every loop
  ControlSystem->UpdateJoysticks();
  shooter->UpdateShooterPosition(targetAngle);
  //TODO Need to implement a timing system to not break the spike (this function doesn't run the compressor at the moment)
  compressorSystem->CompressorSystemPeriodic(allowCompressing);
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
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_ONE]){
	  targetAngle = 100;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_TWO]){
	  targetAngle = 120;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_THREE]){
	  targetAngle = 90;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_FOUR]){
	  targetAngle = 130;
  }
  if(ControlSystem->rightJoystickValues[DISABLE_COMPRESSOR]){
    allowCompressing = false;
  }else{
    allowCompressing = true;
  }
  if(ControlSystem->rightJoystickValues[DRIVE_FOR_DISTANCE]){
	  targetAngle = 100;
	  if(sonar->GetInches("FRONTLEFT") >= 45){
		  DriveRobot(0,-.5);
	  }
	  else{
		  DriveRobot(0,0);
	  }
  }
}
// vim: ts=2:sw=2:et
