#include "HHRobot.h"
#include "NetworkTables/NetworkTable.h"
#include "HHBase.h"
HHRobot::HHRobot():
  ControlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()){
  //sonar(new HHSonar()){
    netTable=NetworkTable::GetTable("datatable");
    right1 = new Talon(DRIVE_RIGHT_MOTOR_ONE, DRIVE_RIGHT_SIDECAR);
    right2 = new Talon(DRIVE_RIGHT_MOTOR_TWO, DRIVE_RIGHT_SIDECAR);
    right3 = new Talon(DRIVE_RIGHT_MOTOR_THREE, DRIVE_RIGHT_SIDECAR);
    left1 = new Talon(DRIVE_LEFT_MOTOR_ONE, DRIVE_LEFT_SIDECAR);
    left2 = new Talon(DRIVE_LEFT_MOTOR_TWO, DRIVE_LEFT_SIDECAR);
    left3 = new Talon(DRIVE_LEFT_MOTOR_THREE, DRIVE_LEFT_SIDECAR);
    rightStick = new Joystick(3);
    leftStick = new Joystick(4);
  }

void HHRobot::Init(){
  printf("Initing\n");
  collector->CollectBallAtSpeed(0);
}
bool HHRobot::CheckJoystickValues(){
  float x=ControlSystem->rightJoystickAxisValues[1];
  float y=ControlSystem->rightJoystickAxisValues[2];
  if((-.1<x && x<.1) && (-.1<y && y<.1)) {
    dashboard->PutBoolValue("Joysticks Valid",true);
    return true;
  }else{
    dashboard->PutBoolValue("Joysticks Valid",false);
    return false;
  }
}
void HHRobot::DriveRobot(float x,float y){
  if(y>1.0f){
    y=1.0f;
  }else if(y!=0.0f&&y<-1.0f){
    y=-1.0f;
  }
  //float leftPower=((y+x)/2+1)*127+1;
  //float rightPower=((y-x)/2+1)*127+1;
  //printf("Left: %f\n", leftPower);
  //printf("Right: %f\n", rightPower);
  //right1->SetRaw(int(rightPower));
  //right2->SetRaw(int(rightPower));
  //right3->SetRaw(int(rightPower));
  //left1->SetRaw(int(leftPower));
  //left2->SetRaw(int(leftPower));
  //left3->SetRaw(int(leftPower));
  printf("Driving and stuff\n");
  printf("Left: %f\n",y+x);
  printf("Right: %f\n",y-x);
  right1->Set(y+x);
  right2->Set(y+x);
  right3->Set(y+x);
  left1->Set(y-x);
  left2->Set(y-x);
  left3->Set(y-x);
}
void HHRobot::UpdateDashboard(){
  dashboard->PutFloatValue("Shooting Power",ControlSystem->throttle);
}
void HHRobot::RunAuto(){
  int step,time;
  compressorSystem->ExtendCollector();
  //TODO I have no idea what rate this loop runs at so we are going to have to fine tune the times
  //Drive for 51 inches/cm/units (or time)
  if(step==2){
    return; } if(step==1 && time<300){
    //TODO Pass the shooting power and sonar distance as variables to the RunAuto function
    //Shoot at a power
    shooter->StartShootingSequence(0.78);
  }else{
    time=0;
    step=2;
  }
  if(step==0 && time<200){
    if(sonar->GetInches("FRONTLEFT")>=51){
      DriveRobot(0,-.5);
    }else{
      DriveRobot(0,0);
    }
  }else{
    time=0;
    step=1;
  }
  //Important periodic things
  netTable->PutNumber("AutoStep",step); //Debugging purposes
  time++;
}

//Main function used to handle periodic tasks on the robot
void HHRobot::Handler(){
  int targetAngle;
  bool allowCompressing;
  //Periodic tasks that should be run by every loop
  ControlSystem->UpdateJoysticks();
  shooter->UpdateShooterPosition(targetAngle);
  //TODO Need to implement a timing system to not break the spike (this function doesn't run the compressor at the moment)
  compressorSystem->CompressorSystemPeriodic(allowCompressing);
  collector->UpdateCollector(shooter->isShooting,shooter->GetAngle());
  //TODO Fix whatever the heck is wrong with this
  //DriveRobot(rightStick->GetRawAxis(1),rightStick->GetRawAxis(2));
  UpdateDashboard();
  //Shooting button
  if(ControlSystem->leftJoystickValues[SHOOTER_FIRE]) {
    shooter->StartShootingSequence(ControlSystem->throttle);
  }
  //Collector button assignments
  if(ControlSystem->GetJoystickButton(2,COLLECTOR_INTAKE)) {
    collector->CollectBall();
  }else if(ControlSystem->GetJoystickButton(2,COLLECTOR_OUTTAKE)) {
    collector->ReleaseBall();
  }else{
    collector->CollectorStop();
  }
  if(rightStick->GetRawButton(COLLECTOR_EXTEND)) {
    compressorSystem->ExtendCollector();
  }
  if(rightStick->GetRawButton(COLLECTOR_RETRACT)) {
    compressorSystem->RetractCollector();
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_ONE]){
    targetAngle=100;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_TWO]){
    targetAngle=120;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_THREE]){
    targetAngle=90;
  }
  if(ControlSystem->leftJoystickValues[SHOOTER_ANGLE_FOUR]){
    targetAngle=130;
  }
  if(ControlSystem->rightJoystickValues[DISABLE_COMPRESSOR]){
    allowCompressing=false;
  }else{
    allowCompressing=true;
  }
  if(ControlSystem->rightJoystickValues[DRIVE_FOR_DISTANCE]){
    targetAngle=100;
    if(sonar->GetInches("FRONTLEFT")>=45){
      DriveRobot(0,-.5);
    }
    else{
      DriveRobot(0,0);
    }
  }
}
// vim: ts=2:sw=2:et
