#include "HHRobot.h"
#include "HHBase.h"
HHRobot::HHRobot():
  ControlSystem(new JoystickController()),
  shooter(new HHShooter()),
  collector(new HHCollector()),
  compressorSystem(new HHCompressor()),
  dashboard(new HHDashboard()){
    left1=new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_ONE);
    left2=new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_TWO);
    left3=new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_THREE);
    right1=new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);
    right2=new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);
    right3=new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);
    frontSonarLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR, SONAR_FRONT_LEFT_DIO);
    frontSonarRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR, SONAR_FRONT_RIGHT_DIO);
    rearSonarLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR, SONAR_REAR_LEFT_DIO);
    rearSonarRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR, SONAR_REAR_RIGHT_DIO);
    frontSonarLeftA=new AnalogChannel(SONAR_FRONT_LEFT_ANA);
    frontSonarRightA=new AnalogChannel(SONAR_FRONT_RIGHT_ANA);
    rearSonarLeftA=new AnalogChannel(SONAR_REAR_LEFT_ANA);
    rearSonarRightA=new AnalogChannel(SONAR_REAR_RIGHT_ANA);
  }
//Functions to get sonar values and return as INCH values
float HHRobot::getFrontSonar(){
  frontSonarLeftD->Set(1);
  frontSonarLeftV=(frontSonarLeftA->GetAverageVoltage()/0.00488f)/2.54f;
  frontSonarLeftD->Set(0);
  //Probably need some sort of delay here
  frontSonarRightD->Set(1);
  frontSonarRightV=(frontSonarRightA->GetAverageVoltage()/0.00488f)/2.54f;
  frontSonarRightD->Set(0);
  //Returns the average (useful for throwing out useless readings)
  return (frontSonarRightV+frontSonarLeftV)/2;
}
float HHRobot::getRearSonar(){
  rearSonarLeftD->Set(1);
  rearSonarLeftV=(rearSonarLeftA->GetAverageVoltage()/0.00488f)/2.54f;
  rearSonarLeftD->Set(0);
  //Probably need some sort of delay here
  rearSonarRightD->Set(1);
  rearSonarRightV=(rearSonarRightA->GetAverageVoltage()/0.00488f)/2.54f;
  rearSonarRightD->Set(0);
  //Returns the average (useful for throwing out useless readings)
  return (rearSonarRightV+rearSonarLeftV)/2;
}
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
