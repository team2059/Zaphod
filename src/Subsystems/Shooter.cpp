#include "Shooter.h"
HHShooter::HHShooter(){
  shooterLeft1=new Jaguar(SHOOTER_LEFT_SIDECAR, SHOOTER_LEFT_MOTOR_ONE);
  shooterLeft2=new Jaguar(SHOOTER_LEFT_SIDECAR, SHOOTER_LEFT_MOTOR_TWO);
  shooterRight1=new Jaguar(SHOOTER_RIGHT_SIDECAR, SHOOTER_RIGHT_MOTOR_ONE);
  shooterRight2=new Jaguar(SHOOTER_RIGHT_SIDECAR, SHOOTER_RIGHT_MOTOR_TWO);
  shooterAngle=new AnalogChannel(SHOOTER_ANGLE_POT);
  e_ShooterState=IDLE_PRESHOT;
}
void HHShooter::StartShootingSequence(float throttle){
  //Changes the enum to tell the shooter to be firing
  e_ShooterState=FIRING;
  // Convert the throttle input to a pwm value
  shootingPower=throttle;
}
//First step in shooting process
bool HHShooter::ShootForAngle(float power, float desiredAngle){
  if(GetAngle() <= desiredAngle){
    ShootRaw(power);
    e_ShooterState=FIRING;
    return true;
  }
  else{
    return false;
  }
}
//Second step in shooting process
//Probably wont need to be used without ShootForAngle
void HHShooter::Lower(float desiredAngle){
  if(GetAngle() >= desiredAngle){
    ShootRaw(-0.1f);
    e_ShooterState=LOWERING;
  }else{
    ShootRaw(0.0f);
    e_ShooterState=IDLE_PRESHOT;
  }
}
//Not needed anywhere other than after/before the shooting process
void HHShooter::StopShooter(){
  if(e_ShooterState == IDLE_PRESHOT){
    ShootRaw(0.0f);
  }
}
//Shouldn't be used in any other class but this one
void HHShooter::ShootRaw(float power){
  shooterLeft1->SetRaw(int(FloatToPWM(power)));
  shooterLeft2->SetRaw(int(FloatToPWM(power)));
  shooterRight1->SetRaw(int(FloatToPWM(-power)));
  shooterRight2->SetRaw(int(FloatToPWM(-power)));
}
//Should be run in a loop
void HHShooter::UpdateShooterPosition(double angle){
  if(e_ShooterState == IDLE_PRESHOT){
    isShooting=false;
    StopShooter();
  }
  else if(e_ShooterState == FIRING){
    isShooting=true;
    if (ShootForAngle(shootingPower,angle)){
      printf("Shooting!\n");
      printf("Shooting at power %d\n",shooterRight1->GetRaw());
    }
    else {
      printf("Done shooting!\n");
      e_ShooterState=IDLE_POSTSHOT;
    }
  }
  else if(e_ShooterState == IDLE_POSTSHOT){
    isShooting=false;
    Lower(40);
  }
}
float HHShooter::FloatToPWM(float input){
  return input*127.0+128;
}
//Returns angle measure in degrees
float HHShooter::GetAngle(){
  float max=-.0003948;
  float min=5.0245547;
  float b=shooterAngle->GetAverageVoltage()-max;
  min=min-max;// ~5.0027
  max=max-max;//=0
  return 300-((b+max)*(300/min));
}
// vim: ts=2:sw=2:et
