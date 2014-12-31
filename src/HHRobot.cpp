#include "HHRobot.h"
#include "NetworkTables/NetworkTable.h"
#include "HHBase.h"
HHRobot::HHRobot():
  drive(new WCDrive(6,1,1,1,2,1,3,2,1,2,2,2,3)),
  driveStick(new Extreme3dPro(1)),
  shootStick(new Extreme3dPro(2)),
  compressor(new AirCompressor(2,5,1,3)),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  dashboard(new SmartDash()){
    //sonar(new HHSonar()){}
    driveTable=NetworkTable::GetTable("ZaphodDrive");
    shooterTable=NetworkTable::GetTable("ZaphodShooter");
    collectorTable=NetworkTable::GetTable("ZaphodCollector");
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
  compressor->StartCompressor();
}
bool HHRobot::CheckJoystickValues(){
  float x=driveStick->GetJoystickAxis("x");
  float y=driveStick->GetJoystickAxis("y");
  if((-.1<x && x<.1) && (-.1<y && y<.1)) {
    dashboard->PutBoolValue("Joysticks Valid",true);
    return true;
  }else{
    dashboard->PutBoolValue("Joysticks Valid",false);
    return false;
  }
}
void HHRobot::UpdateDashboard(){
  dashboard->PutFloatValue("Shooting Power",shootStick->GetThrottle());
}
void HHRobot::RunAuto(){
  timer->Reset();
  int step,time;
  //CollectorExtend
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
  //Periodic tasks that should be run by every loop
  shooter->UpdateShooterPosition(targetAngle);
  driveStick->handler();
  shootStick->handler();
  collector->UpdateCollector(shooter->isShooting,shooter->GetAngle());
  //TODO Fix whatever the heck is wrong with this
  drive->Update(6,driveStick->GetJoystickAxis("z")+driveStick->GetJoystickAxis("x"),driveStick->GetJoystickAxis("y"));
  UpdateDashboard();
  //Shooting button
  if(shootStick->ButtonValue[1]){
    shooter->StartShootingSequence(shootStick->GetThrottle());
  }
  //Collector button assignments
  if(driveStick->GetJoystickButton(COLLECTOR_INTAKE)) {
    collector->CollectBall();
    collectorTable->PutNumber("Current Collector Speed",1);
  }else if(driveStick->GetJoystickButton(COLLECTOR_OUTTAKE)) {
    collectorTable->PutNumber("Current Collector Speed",-1);
    collector->ReleaseBall();
  }else{
    collectorTable->PutNumber("Current Collector Speed",0);
    collector->CollectorStop();
  }
  if(driveStick->GetJoystickButton(COLLECTOR_EXTEND)){
    //TODO extend collector
  }
  if(driveStick->GetJoystickButton(COLLECTOR_RETRACT)){
    //TODO retract collector
  }
  if(shootStick->GetJoystickButton(SHOOTER_ANGLE_ONE)){
    targetAngle=100;
  }
  if(driveStick->GetJoystickButton(SHOOTER_ANGLE_TWO)){
    targetAngle=120;
  }
  if(shootStick->GetJoystickButton(SHOOTER_ANGLE_THREE)){
    targetAngle=90;
  }
  if(shootStick->GetJoystickButton(SHOOTER_ANGLE_FOUR)){
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
  shooterTable->PutNumber("Current Shooter Power",shootStick->GetThrottle()*100);
  shooterTable->PutNumber("Current Shooter Power (raw)",shootStick->GetThrottle() * 127.0f + 128);
}
// vim: ts=2:sw=2:et
