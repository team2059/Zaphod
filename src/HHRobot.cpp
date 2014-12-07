#include "HHRobot.h"
#include "NetworkTables/NetworkTable.h"
#include "HHBase.h"
HHRobot::HHRobot():
  controlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()){
    //sonar(new HHSonar()){}
    driveTable=NetworkTable::GetTable("ZaphodDrive");
    shooterTable=NetworkTable::GetTable("ZaphodShooter");
    collectorTable=NetworkTable::GetTable("ZaphodCollector");
    right1 = new Talon(DRIVE_RIGHT_SIDECAR,DRIVE_RIGHT_MOTOR_ONE);
    right2 = new Talon(DRIVE_RIGHT_SIDECAR,DRIVE_RIGHT_MOTOR_TWO);
    right3 = new Talon(DRIVE_RIGHT_SIDECAR,DRIVE_RIGHT_MOTOR_THREE);
    left1 = new Talon(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_ONE);
    left2 = new Talon(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_TWO);
    left3 = new Talon(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_THREE);
    shooterTable->PutNumber("Target Shooter Angle",90);
    timer = new Timer();
    lastTime = 0;
  }
void HHRobot::Init(){
  printf("Initing\n");
  printf("Code Version: %f\n",CODE_VERSION);
  collector->CollectBallAtSpeed(0);
  //Put table values initally to avoid annoying refreshing
  shooterTable->PutNumber("Target Shooter Angle",90);
  shooterTable->PutNumber("Current Shooter Angle",-420);
  timer->Start();
  compressorSystem->StartCompressor();
}
bool HHRobot::CheckJoystickValues(){
  float x=controlSystem->GetJoystickAxis(1,"x");
  float y=controlSystem->GetJoystickAxis(1,"y");
  if((-.1<x && x<.1) && (-.1<y && y<.1)) {
    dashboard->PutBoolValue("Joysticks Valid",true);
    return true;
  }else{
    dashboard->PutBoolValue("Joysticks Valid",false);
    return false;
  }
}
void HHRobot::DriveRobot(float y,float x){
  if(y>1.0f){
    y=1.0f;
  }else if(y!=0.0f&&y<-1.0f){
    y=-1.0f;
  }
  float leftPower=((y-x)/2+1)*127+1;
  float rightPower=((y+x)/2+1)*127+1;
  if(controlSystem->GetJoystickAxis(1,"throttle")>0.5f){
    leftPower*=-1;
    rightPower*=-1;
  }
  driveTable->PutNumber("joystickRawX",x);
  driveTable->PutNumber("joystickRawY",y);
  driveTable->PutNumber("leftSidePower",leftPower);
  driveTable->PutNumber("rightSidePower",rightPower);
  driveTable->PutNumber("right1MotorPower",right1->GetRaw());
  driveTable->PutNumber("right2MotorPower",right2->GetRaw());
  driveTable->PutNumber("right3MotorPower",right3->GetRaw());
  driveTable->PutNumber("left1MotorPower",left1->GetRaw());
  driveTable->PutNumber("left2MotorPower",left2->GetRaw());
  driveTable->PutNumber("left3MotorPower",left3->GetRaw());
  right1->SetRaw(int(rightPower));
  right2->SetRaw(int(rightPower));
  right3->SetRaw(int(rightPower));
  left1->SetRaw(int(leftPower));
  left2->SetRaw(int(leftPower));
  left3->SetRaw(int(leftPower));
  //printf("Left: %f\n",y+x);
  //printf("Right: %f\n",y-x);
  //right1->Set(y+x);
  //right2->Set(y+x);
  //right3->Set(y+x);
  //left1->Set(y-x);
  //left2->Set(y-x);
  //left3->Set(y-x);
}
void HHRobot::UpdateDashboard(){
  dashboard->PutFloatValue("Shooting Power",controlSystem->GetThrottle());
}
void HHRobot::RunAuto(){
  timer->Reset();
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
  time++;
}

//Main function used to handle periodic tasks on the robot
void HHRobot::Handler(){
  double targetAngle = shooterTable->GetNumber("Target Shooter Angle");
  bool allowCompressing = true;
  //Periodic tasks that should be run by every loop
  shooter->UpdateShooterPosition(targetAngle);
  if(timer->Get()-lastTime>=0.5f){
    // Update compressor when current time-last time is more than .5 seconds
    lastTime=timer->Get();
    compressorSystem->CompressorSystemPeriodic(allowCompressing);
  }
  collector->UpdateCollector(shooter->isShooting,shooter->GetAngle());
  //TODO Fix whatever the heck is wrong with this
  DriveRobot(controlSystem->GetJoystickAxis(1,"z")+controlSystem->GetJoystickAxis(1,"x"),controlSystem->GetJoystickAxis(1,"y"));
  UpdateDashboard();
  //Shooting button
  if(controlSystem->GetJoystickButton(2,SHOOTER_FIRE)){
    shooter->StartShootingSequence(controlSystem->GetThrottle());
  }
  //Collector button assignments
  if(controlSystem->GetJoystickButton(1,COLLECTOR_INTAKE)) {
    collector->CollectBall();
    collectorTable->PutNumber("Current Collector Speed",1);
  }else if(controlSystem->GetJoystickButton(1,COLLECTOR_OUTTAKE)) {
    collectorTable->PutNumber("Current Collector Speed",-1);
    collector->ReleaseBall();
  }else{
    collectorTable->PutNumber("Current Collector Speed",0);
    collector->CollectorStop();
  }
  if(controlSystem->GetJoystickButton(1,COLLECTOR_EXTEND)){
    compressorSystem->ExtendCollector();
  }
  if(controlSystem->GetJoystickButton(1,COLLECTOR_RETRACT)){
    compressorSystem->RetractCollector();
  }
  if(controlSystem->GetJoystickButton(2,SHOOTER_ANGLE_ONE)){
    targetAngle=100;
  }
  if(controlSystem->GetJoystickButton(2,SHOOTER_ANGLE_TWO)){
    targetAngle=120;
  }
  if(controlSystem->GetJoystickButton(2,SHOOTER_ANGLE_THREE)){
    targetAngle=90;
  }
  if(controlSystem->GetJoystickButton(2,SHOOTER_ANGLE_FOUR)){
    targetAngle=130;
  }
  shooterTable->PutNumber("Target Shooter Angle",targetAngle);
  //TODO: Fix whatever this is supposed to do
  //if(controlSystem->rightJoystickValues[DRIVE_FOR_DISTANCE]){}
  if(false){
    targetAngle=100;
    if(sonar->GetInches("FRONTLEFT")>=45){
      DriveRobot(0,-.5);
    } else{
      DriveRobot(0,0);
    }
  }
  // Misc periodic tasks
  //
  // Shooting stuff
  shooterTable->PutNumber("Current Shooter Angle",shooter->GetAngle());
  shooterTable->PutNumber("Current Shooter State",shooter->e_ShooterState);
  shooterTable->PutNumber("Current Shooter Power",controlSystem->GetThrottle()*100);
  shooterTable->PutNumber("Current Shooter Power (raw)",controlSystem->GetThrottle() * 127.0f + 128);
}
// vim: ts=2:sw=2:et
