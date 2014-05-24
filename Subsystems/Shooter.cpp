#include "Shooter.h"

ZaphodShooter::ZaphodShooter()
{
  shooterLeft1 = new Jaguar(SHOOTER_LEFT_SIDECAR, SHOOTER_LEFT_MOTOR_ONE);
  shooterLeft2 = new Jaguar(SHOOTER_LEFT_SIDECAR, SHOOTER_LEFT_MOTOR_TWO);
  shooterRight1 = new Jaguar(SHOOTER_RIGHT_SIDECAR, SHOOTER_RIGHT_MOTOR_ONE);
  shooterRight2 = new Jaguar(SHOOTER_RIGHT_SIDECAR, SHOOTER_RIGHT_MOTOR_TWO);

  shooterAngle = new AnalogChannel(SHOOTER_ANGLE_POT);
  e_ShooterState = IDLE_PRESHOT;
}

void ZaphodShooter::startShootingSequence()
{
  //Changes the enum to tell the shooter to be firing
  e_ShooterState = FIRING;
}

//First step in shooting process
void ZaphodShooter::shootForAngle(float power, float desiredAngle)
{
  if(getAngle() <= desiredAngle)
  {
    shootRaw(power);
    e_ShooterState = FIRING;
  }
  else
  {
    e_ShooterState = IDLE_POSTSHOT;
  }
}

//Second step in shooting process
//Probably wont need to be used without shootForAngle
void ZaphodShooter::lower(float desiredAngle)
{
  if(getAngle() >= desiredAngle)
  {
    shootRaw(-0.1f);
    e_ShooterState = LOWERING;
  }
  else
  {
    shootRaw(0.0f);
    e_ShooterState = IDLE_PRESHOT;
  }
}

//Not needed anywhere other than after/before the shooting process
void ZaphodShooter::stopShooter()
{
  if(e_ShooterState == IDLE_PRESHOT)
  {
    shootRaw(0.0f);
  }
}

//Shouldn't be used in any other class but this one
void ZaphodShooter::shootRaw(float power)
{
  shooterLeft1->SetRaw(int(floatToPWM(power)));
  shooterLeft2->SetRaw(int(floatToPWM(power)));
  shooterRight1->SetRaw(int(floatToPWM(-power)));
  shooterRight2->SetRaw(int(floatToPWM(-power)));
}

void ZaphodShooter::updateShooterPosition()
{
  if(e_ShooterState == IDLE_PRESHOT)
  {
    stopShooter();
  }
  if(e_ShooterState == FIRING)
  {
    shootForAngle(1,110);
  }
  if(e_ShooterState == IDLE_POSTSHOT)
  {
    lower(40);
  }
}

float ZaphodShooter::floatToPWM(float input)
{
  return input * 127.0 + 128;
}

//Returns angle measure in degrees
float ZaphodShooter::getAngle()
{
  float max = -.0003948;                                                           
  float min = 5.0245547;                                                           
  float b = shooterAngle->GetAverageVoltage() - max;                                                               
  min = min - max; // ~5.0027                                                      
  max = max - max; //=0                                                            
  return 300 - ((b + max) * (300 / min));
}
