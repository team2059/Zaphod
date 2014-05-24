#include "ZaphodRobot.h"
#include "ZaphodBase.h"

ZaphodRobot::ZaphodRobot():
  ControlSystem(new JoystickController()),
  shooter(new ZaphodShooter()),
  collector(new ZaphodCollector())
{
  left1 = new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_ONE);
  left2 = new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_TWO);
  left3 = new Jaguar(DRIVE_LEFT_SIDECAR, DRIVE_LEFT_MOTOR_THREE);
  right1 = new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);
  right2 = new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);
  right3 = new Jaguar(DRIVE_RIGHT_SIDECAR, DRIVE_RIGHT_MOTOR_ONE);

  compressor = new Compressor(COMPRESSOR_GAUGE_SIDECAR, COMPRESSOR_GAUGE, COMPRESSOR_RELAY_SIDECAR, COMPRESSOR_RELAY);
  solenoid1 = new Solenoid(COMPRESSOR_SOLENOID_ONE);
  solenoid2 = new Solenoid(COMPRESSOR_SOLENOID_TWO);

  frontSonarLeftD = new DigitalOutput(SONAR_LEFT_DIO_SIDECAR, SONAR_FRONT_LEFT_DIO);
  frontSonarRightD = new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR, SONAR_FRONT_RIGHT_DIO);
  rearSonarLeftD = new DigitalOutput(SONAR_LEFT_DIO_SIDECAR, SONAR_REAR_LEFT_DIO);
  rearSonarRightD = new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR, SONAR_REAR_RIGHT_DIO);

  frontSonarLeftA = new AnalogChannel(SONAR_FRONT_LEFT_ANA);
  frontSonarRightA = new AnalogChannel(SONAR_FRONT_RIGHT_ANA);
  rearSonarLeftA = new AnalogChannel(SONAR_REAR_LEFT_ANA);
  rearSonarRightA = new AnalogChannel(SONAR_REAR_RIGHT_ANA);
}

//Functions to get sonar values and return as INCH values

float ZaphodRobot::getFrontSonar()
{
  frontSonarLeftD->Set(1);
  frontSonarLeftV = (frontSonarLeftA->GetAverageVoltage()/0.00488f)/2.54f;
  frontSonarLeftD->Set(0);
  //Probably need some sort of delay here

  frontSonarRightD->Set(1);
  frontSonarRightV = (frontSonarRightA->GetAverageVoltage()/0.00488f)/2.54f;
  frontSonarRightD->Set(0);

  //Returns the average (useful for throwing out useless readings)
  return (frontSonarRightV+frontSonarLeftV)/2;
}

float ZaphodRobot::getRearSonar()
{
  rearSonarLeftD->Set(1);
  rearSonarLeftV = (rearSonarLeftA->GetAverageVoltage()/0.00488f)/2.54f;
  rearSonarLeftD->Set(0);
  //Probably need some sort of delay here

  rearSonarRightD->Set(1);
  rearSonarRightV = (rearSonarRightA->GetAverageVoltage()/0.00488f)/2.54f;
  rearSonarRightD->Set(0);

  //Returns the average (useful for throwing out useless readings)
  return (rearSonarRightV+rearSonarLeftV)/2;
}

//Main function used to handle periodic tasks on the robot
 
void ZaphodRobot::handler()
{
  //Periodic tasks that should be run by every loop
  ControlSystem->getRightJoystick();
  ControlSystem->getLeftJoystick();
  shooter->updateShooterPosition();
  if(ControlSystem->leftJoystickValues[SHOOTER_FIRE])
  {
    //TODO Needs a power input
    shooter->startShootingSequence();
    //TODO Needs to be moved to run with the shooter class
    collector->spinWithShot(shooter->getAngle());
  }

}
