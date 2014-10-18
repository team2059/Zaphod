//Includes{{{
#include "WPILib.h"
#include "SmartDashboard/SmartDashboard.h"
#include <iostream>
#include <math.h>
#include <sstream>
//}}}
class RobotDemo : public SimpleRobot
{
  //Declarations{{{
  RobotDrive myRobot;
  bool collectorExtended,shooting,compressing, compressorEnabled, hasShot, waitingToFire, shooter_idle;
  float upLimit,throttle;
  Joystick Rstick,Lstick;
  Solenoid collectorSole1,collectorSole2;
  Compressor compressor;
  Jaguar Left1,Left2,Left3,Right1,Right2,Right3,RightArmMotor1,RightArmMotor2,LeftArmMotor1,LeftArmMotor2,CollectorMotor1;
  AnalogChannel armPot,BallSonicLeft,BallSonicRight,WallSonicLeft,WallSonicRight;
  DigitalOutput BallLeft,BallRight,WallLeft,WallRight;
  //}}}
public:
  RobotDemo():
    //Initializations{{{
    //Joysticks
    Rstick(1),
    Lstick(2),
    //Pot
    armPot(6),
    //Ultrasonic
    BallSonicLeft(1),
    BallSonicRight(2),
    WallSonicLeft(3),
    WallSonicRight(4),
    BallLeft(1,4),
    WallLeft(1,5),
    BallRight(2,4),
    WallRight(2,5),
    //Compressor
    compressor(2,5,1,3),
    //Solenoids
    collectorSole1(1),
    collectorSole2(2),
    //Drive Motors
    Left1(1,1),
    Left2(1,2),
    Left3(1,3),
    Right1(2,1),
    Right2(2,2),
    Right3(2,3),
    //Shooter Motors
    LeftArmMotor1(1,4),
    LeftArmMotor2(1,5),
    RightArmMotor1(2,4),
    RightArmMotor2(2,5),
    //Collector Motor
    CollectorMotor1(1,6),
    myRobot(Left1,Left2,Right1,Right2){
    GetWatchdog().SetEnabled(false);
  }
  //}}}
  //{{{shootRobot
  void shootRobot(float power){
      setMotorValue(4,1,cvt(power));
      setMotorValue(5,1,cvt(power));
      setMotorValue(4,2,cvt(-power));
      setMotorValue(5,2,cvt(-power));
  }
  //}}}
  //RobotInit{{{
  void RobotInit(){
    DashboardSetup();
    upLimit=100.0;
    //compressor.Start();
    shooting=false;
    compressing=true;
    compressorEnabled=true;
    hasShot=false;
    waitingToFire=false;
    shooter_idle=true;
    throttle=(-Lstick.GetRawAxis(4)+1)/2;
  }
  //}}}
  //DashboardSetup{{{
  void DashboardSetup(){
    SmartDashboard::PutNumber("Throttle",throttle);
    SmartDashboard::PutNumber("upLimit",100.0f);
    SmartDashboard::PutNumber("armPot",potToDegrees(armPot.GetAverageVoltage()));
    SmartDashboard::PutNumber("Log Level",1.0f);
    SmartDashboard::PutNumber("ArmSpeed",0.0);
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage(),true));
    //Autonomous values
    SmartDashboard::PutNumber("AutoSpeed",0.95f);
    SmartDashboard::PutNumber("Auto Distance",51.0f);
    SmartDashboard::PutNumber("Collector Speed",1.0f);
    SmartDashboard::PutNumber("AutoPower",0.74f);
    SmartDashboard::PutNumber("AutoCorrection",0.05f);
    SmartDashboard::PutNumber("Initial Drive Delay",2.0f);
    SmartDashboard::PutNumber("Inital Drive Timeout",4.5f);
    SmartDashboard::PutNumber("First Shot Start",0.5f);
    SmartDashboard::PutNumber("First Shot Stop",1.0f);
    SmartDashboard::PutNumber("Reverse direction start",0.0f);
    SmartDashboard::PutNumber("Reverse direction stop",2.5f);
    SmartDashboard::PutNumber("Second Drive Start",1.0f);
    SmartDashboard::PutNumber("Second Drive Timeout",2.5f);
    SmartDashboard::PutNumber("Second Shot Start",0.5f);
    SmartDashboard::PutNumber("Second Shot Stop",1.0f);
    SmartDashboard::PutNumber("Autonomous step",0.0f);
    SmartDashboard::PutNumber("Autonomous sequence",2.0f);
    //Shooter presets
    SmartDashboard::PutNumber("ShortRange",0.465f); //Power for the shooter when against the low goal
    SmartDashboard::PutNumber("ShooterButtonPower10",0.855f);
    SmartDashboard::PutNumber("ShooterButtonPower7",1.0f);
    SmartDashboard::PutNumber("ShooterButtonPower8",0.5f);
    //Bool switches
    SmartDashboard::PutBoolean("HalfPower",false);
    SmartDashboard::PutBoolean("OneBallAuto",false);
    SmartDashboard::PutBoolean("Use Ultrasonic",true);
    SmartDashboard::PutBoolean("Daniel Mode",false);
    SmartDashboard::PutBoolean("CollectorState",false);
    SmartDashboard::PutBoolean("Compressor Running",compressing);
    SmartDashboard::PutBoolean("Ignore Pot",false);
    SmartDashboard::PutBoolean("Compressor Enabled",compressorEnabled);
  }
  //}}}
  //updateDashboard{{{
  void updateDashboard(){
    SmartDashboard::PutNumber("Throttle",throttle);
    SmartDashboard::PutNumber("armPot",potToDegrees(armPot.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Wall Right",voltToDistance(WallSonicRight.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Ball Left",voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right",voltToDistance(BallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("upLimit",upLimit);
    SmartDashboard::PutBoolean("Compressor Running",compressing);
    compressorEnabled=SmartDashboard::GetBoolean("Compressor Enabled");
    if(upLimit > 167){
      upLimit=167;
    }
  }
  //}}}
  //driveRobot{{{
  void driveRobot(float x,float y){
    if(y>1.0f){
      y=1.0f;
    }else if(y!=0.0f&&y<-1.0f){
      y=-1.0f;
    }
    if(SmartDashboard::GetBoolean("HalfPower")){
      x/=3;
      y/=3;
      printf("Running drive motors at half power\n");
    }
    int leftPower=((y+x)/2+1)*127+1;
    int rightPower=((y-x)/2+1)*127+1;
    setMotorValue(1,1,leftPower);
    setMotorValue(2,1,leftPower);
    setMotorValue(3,1,leftPower);
    setMotorValue(1,2,rightPower);
    setMotorValue(2,2,rightPower);
    setMotorValue(3,2,rightPower);
  }
  //}}}
  //voltToDistance{{{
  float voltToDistance(float a,bool wall=false){
    if(wall){
      return (a/0.00488f)/2.54f;
    }else{
      return (a/0.000976562f)/25.4f;
    }
  }
  //}}}
  //potToDegrees{{{
  float potToDegrees(float a) {
    float max = -.0003948;
    float min = 5.0245547;
    float b = a - max;
    min = min - max; // ~5.0027
    max = max - max; //=0
    return 300 - ((b + max) * (300 / min));
  }
  //}}}
  //cvt{{{
  int cvt(float input){
    return input * 127.0f + 128;
  }
  //}}}
  //setMotorValue{{{
  void setMotorValue(int motor,int subwayStation=1,int value=127){
    if(subwayStation==1){
      //subwayStation1{{{
      switch(motor){
      case 1:
        Left1.SetRaw(value);
        break;
      case 2:
        Left2.SetRaw(value);
        break;
      case 3:
        Left3.SetRaw(value);
        break;
      case 4:
        LeftArmMotor1.SetRaw(value);
        break;
      case 5:
        LeftArmMotor2.SetRaw(value);
        break;
      case 6:
        CollectorMotor1.SetRaw(value);
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      }
      //}}}
    }else if(subwayStation==2){
      //subwayStation2{{{
      switch(motor){
        //Shooter motors
      case 1:
        Right1.SetRaw(value);
        break;
      case 2:
        Right2.SetRaw(value);
        break;
      case 3:
        Right3.SetRaw(value);
        break;
      case 4:
        RightArmMotor1.SetRaw(value);
        break;
      case 5:
        RightArmMotor2.SetRaw(value);
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      }
      //}}}
    }
  }
  //}}}
  //runCompressor{{{
  void runCompressor(int i, int refreshInterval){
    if(i%refreshInterval==0){
      if(compressorEnabled){
        printf("compressorEnabled=true\n");
      }else{
        printf("compressorEnabled=false\n");
      }
    }
    if(i%refreshInterval==0&&compressing&&(compressor.GetPressureSwitchValue()==1||!compressorEnabled)){
      printf("Stopping compressor\n");
      compressing=false;
      compressor.Stop();
    }
    if(i%refreshInterval==0&&!compressing&&compressor.GetPressureSwitchValue()==0&&(shooter_idle&&compressorEnabled)){
      printf("Starting compressor\n");
      compressing=true;
      compressor.Start();
    }
  }
    //}}}
  //shooter_clear_to_fire{{{
  // Function used to centralize the pre-shot checks (collector state, pot angle, etc.)
  bool shooter_clear_to_fire(){
    bool clear_to_shoot;
    if(collectorExtended==true){ //Check that the collector is in the out position
      clear_to_shoot=true;
    }else{
      clear_to_shoot=false;
    }
    //Used for debugging purposes
    if(clear_to_shoot){
      printf("The robot is clear to shoot!\n");
    }
    return clear_to_shoot; //Returns true if all of the shooting safetys are met
  }
  //}}}
  //{{{shooter_fire
  bool shooter_fire(bool shooter_clear, float shooter_speed, float shooter_max_angle, float shooter_current_angle){
    //Fire the shooter motors at the given shooter_speed while the shooter_max_angle hasn't been hit and that it is clear to shoot
    if(shooter_clear==true){
      printf("Shooter clear");
    }else{
      printf("Shooter not clear");
    }
    printf("Max angle: %f, Current angle: %f, shooter_speed: %f\n",shooter_max_angle,shooter_current_angle,shooter_speed);
    if(shooter_max_angle>=shooter_current_angle && shooter_clear==true){
      printf("Shooting @ %d",shooter_speed);
      setMotorValue(4,1,cvt(shooter_speed));
      setMotorValue(5,1,cvt(shooter_speed));
      setMotorValue(4,2,cvt(-shooter_speed));
      setMotorValue(5,2,cvt(-shooter_speed));
      setMotorValue(6,1,1);
      return true;
    }
    else{
      shooter_fired(1);
      return false;
    }
  }
  //}}}
  //{{{shooter_lower
  void shooter_lower(float shooter_speed, float shooter_lower_limit, float shooter_current_angle){
    //Used to lower the shooter to the lower limit
    if(shooter_lower_limit<=shooter_current_angle){
      setMotorValue(4,1,cvt(shooter_speed));
      setMotorValue(5,1,cvt(shooter_speed));
      setMotorValue(4,2,cvt(-shooter_speed));
      setMotorValue(5,2,cvt(-shooter_speed));
      setMotorValue(6,1,0);
    }else{
     //Important part the stops the whole shooting sequence and tells the user that the shooter is back at its original state
     shooter_idle=true;
     compressorEnabled=true;
     SmartDashboard::PutBoolean("Compressor Enabled",true);
     shooter_fired(0);
    }
  }
  //}}}
  //{{{shooter_stop
  void shooter_stop(){
    setMotorValue(4,1,cvt(0.0));
    setMotorValue(5,1,cvt(0.0));
    setMotorValue(4,2,cvt(0.0));
    setMotorValue(5,2,cvt(0.0));
    setMotorValue(6,1,0);
  }
  //}}}
  //shooter_fired{{{
  // This function is used to check if the shooter has finished its cycle
  bool shooter_fired(int mode){
    switch(mode){
      case 0:
        hasShot=false;
        return hasShot;
        break;
      case 1:
        hasShot=true;
        return hasShot;
        break;
      case 2:
        return hasShot;
        break;
      default:
        break;
    }
  }
  //}}}
  //Autonomous{{{
  void Autonomous(){
    //Initializations{{{
    myRobot.SetSafetyEnabled(false);
    int i=0;
    int c=0;
    float power=SmartDashboard::GetNumber("AutoPower");
    float correction=SmartDashboard::GetNumber("AutoCorrection");
    int currentStep=0;
    compressing=false;
    collectorSole1.Set(false);
    collectorSole2.Set(true);
    WallLeft.Set(1);
    BallLeft.Set(0);
    WallRight.Set(1);
    BallRight.Set(0);
    SmartDashboard::PutBoolean("CollectorState",true);
    //}}}
    while(IsEnabled()&&IsAutonomous()){
      if(SmartDashboard::GetNumber("Autonomous sequence")==0){
        //Autonomous0{{{
        //Drive{{{
        if(currentStep==0){
          if(voltToDistance(WallSonicLeft.GetAverageVoltage(),true)>=SmartDashboard::GetNumber("Auto Distance")){
            driveRobot(-1.0f,correction);
          }else{
            driveRobot(0.0f,0.0f);
          }
          if(c==SmartDashboard::GetNumber("Inital Drive Timeout")*200){
            driveRobot(0.0f,0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Shoot{{{
        if(currentStep==1&&c>SmartDashboard::GetNumber("First Shot Start")*200){
          if(SmartDashboard::GetBoolean("Ignore Pot")||upLimit>=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(power);
          }else{
            shootRobot(0.0f);
          }
          setMotorValue(6, 1, 1);
          if(c==(SmartDashboard::GetNumber("First Shot Stop"))*200){
            shootRobot(0.0f);
            setMotorValue(6, 1, 0);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Lower Shooter{{{
        if(currentStep==2&&c>SmartDashboard::GetNumber("Reverse direction start")*200){
          if(40.0f<=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(-0.3f);
          }else{
            shootRobot(0.0f);
          }
          if(c==(3.0f)*200){
            shootRobot(0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //}}}
      }else if(SmartDashboard::GetNumber("Autonomous sequence")==1){
        //Autonomous1{{{
        //Drive{{{
        if(currentStep==0){
          if(voltToDistance(WallSonicLeft.GetAverageVoltage(),true)>=SmartDashboard::GetNumber("Auto Distance")){
            driveRobot(-1.0f,correction);
          }else{
            driveRobot(0.0f,0.0f);
          }
          if(c==SmartDashboard::GetNumber("Inital Drive Timeout")*200){
            driveRobot(0.0f,0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Shoot{{{
        if(currentStep==1&&c>SmartDashboard::GetNumber("First Shot Start")*200){
          if(SmartDashboard::GetBoolean("Ignore Pot")||upLimit>=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(power);
          }else{
            shootRobot(0.0f);
          }
          setMotorValue(6, 1, 1);
          if(c==(SmartDashboard::GetNumber("First Shot Stop"))*200){
            shootRobot(0.0f);
            setMotorValue(6, 1, 0);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Drive Backwards{{{
        if(currentStep==2&&c>SmartDashboard::GetNumber("Reverse direction start")*200){
          driveRobot(1.0f,correction);
          if(40.0f<=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(-0.2f);
          }else{
            shootRobot(0.0f);
          }
          if(c==(SmartDashboard::GetNumber("Reverse direction stop"))*200){
            driveRobot(0.0f,0.0f);
            shootRobot(0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Drive{{{
        if(currentStep==3&&c>SmartDashboard::GetNumber("Second Drive Start")*200){
          if(voltToDistance(WallSonicLeft.GetAverageVoltage(),true)>=SmartDashboard::GetNumber("Auto Distance")){
            driveRobot(-1.0f,correction);
          }else{
            driveRobot(0.0f,0.0f);
          }
          if(c==(SmartDashboard::GetNumber("Inital Drive Timeout"))*200){
            driveRobot(0.0f,0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Shoot{{{
        if(currentStep==4&&c>(SmartDashboard::GetNumber("Second Shot Start"))*200){
          if(SmartDashboard::GetBoolean("Ignore Pot")||upLimit>=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(power);
          }else{
            shootRobot(0.0f);
          }
          setMotorValue(6, 1, 1);
          if(c==(SmartDashboard::GetNumber("First Shot Stop"))*200){
            shootRobot(0.0f);
            setMotorValue(6, 1, 0);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //}}}
      }else if(SmartDashboard::GetNumber("Autonomous sequence")==2){
        //Autonomous2{{{
        //Drive{{{
        if(currentStep==0&&c>SmartDashboard::GetNumber("Initial Drive Delay")*200){
          setMotorValue(6, 1, SmartDashboard::GetNumber("Collector Speed"));
          if(voltToDistance(WallSonicLeft.GetAverageVoltage(),true)>=SmartDashboard::GetNumber("Auto Distance")){
            driveRobot(-1*(SmartDashboard::GetNumber("AutoSpeed")),correction);
          }else{
            driveRobot(0.0f,0.0f);
          }
          if(c==SmartDashboard::GetNumber("Inital Drive Timeout")*200){
            setMotorValue(6, 1, 0);
            driveRobot(0.0f,0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Release Ball{{{
        if(currentStep==1){
          setMotorValue(6, 1, 102);
          if(c==50){
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Shoot{{{
        if(currentStep==2&&c>SmartDashboard::GetNumber("First Shot Start")*200){
          if(SmartDashboard::GetBoolean("Ignore Pot")||upLimit>=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(power);
          }else{
            shootRobot(0.0f);
          }
          if(c==SmartDashboard::GetNumber("First Shot Stop")*200){
            shootRobot(0.0f);
            setMotorValue(6, 1, 0);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Lower Shooter{{{
        if(currentStep==3){
          if(40.0f<=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(-0.1f);
          }else{
            shootRobot(0.0f);
          }
          if(c==1*200){
            shootRobot(0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Collect Ball{{{
        if(currentStep==4&&c>SmartDashboard::GetNumber("Second Shot Start")){
          setMotorValue(6, 1, 1);
          if(c==SmartDashboard::GetNumber("Second Shot Stop")*200){
            setMotorValue(6, 1, 0);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //Shoot{{{
        if(currentStep==5&&c>(SmartDashboard::GetNumber("Second Shot Start"))*200){
          if(SmartDashboard::GetBoolean("Ignore Pot")||upLimit>=potToDegrees(armPot.GetAverageVoltage())){
            shootRobot(power);
          }else{
            shootRobot(0.0f);
          }
          setMotorValue(6, 1, 1);
          if(c==(SmartDashboard::GetNumber("First Shot Stop"))*200){
            setMotorValue(6, 1, 0);
            shootRobot(0.0f);
            currentStep++;
            c=0;
          }
        }
        //}}}
        //}}}
      }
      SmartDashboard::PutNumber("Autonomous step", currentStep);
      updateDashboard();
      //Compressor{{{
      if(SmartDashboard::GetBoolean("Compressor Enabled")){
        runCompressor(i,100);
      }
      //}}}
      i++;
      c++;
      Wait(0.005f);
    compressing=false;
    compressor.Stop();
  }
}
  //}}}
  //Teleop{{{
  void OperatorControl(){
    //Initializations{{{
    myRobot.SetSafetyEnabled(false);
    int i=0;
    collectorSole1.Set(true);
    collectorSole2.Set(false);
    compressing=false;
    SmartDashboard::PutBoolean("CollectorState",false);
    //}}}
    while(IsEnabled()&&IsOperatorControl()){
      //Joystick{{{
      //Throttle values{{{
      if(Lstick.GetRawButton(9)==1){
        throttle=(-Lstick.GetRawAxis(4)+1)/2;
      }else if(Lstick.GetRawButton(10)){
        throttle=SmartDashboard::GetNumber("ShooterButtonPower10");
      }else if(Lstick.GetRawButton(7)){
        throttle=SmartDashboard::GetNumber("ShooterButtonPower7");
      }else if(Lstick.GetRawButton(8)){
        throttle=SmartDashboard::GetNumber("ShooterButtonPower8");
      }
      //}}}
      //Shooter upLimit{{{
      if(Lstick.GetRawButton(3)){
        upLimit=100.0f;
      }
      if(Lstick.GetRawButton(4)){
        upLimit=120.0f;
      }
      if(Lstick.GetRawButton(5)){
        upLimit=90.0f;
      }
      if(Lstick.GetRawButton(6)){
        upLimit=130.0f;
      }
      //}}}
        //Shoot{{{
      if(Lstick.GetRawButton(1)==1){
        compressorEnabled=false;
        SmartDashboard::PutBoolean("Compressor Enabled",false);
        if(compressing){
          printf("Forcing compressor off\n");
          compressor.Stop();
        }
        compressing=false;
        shooter_idle=false; //Cause the robot to start the shooting sequence
      }
        //}}}
      //Collector Arm{{{
      if(Rstick.GetRawButton(9)==1){
        SmartDashboard::PutBoolean("CollectorState",true);
        collectorExtended=true;
        collectorSole1.Set(false);
        collectorSole2.Set(true);
      }else if(Rstick.GetRawButton(10)==1){
        SmartDashboard::PutBoolean("CollectorState",false);
        collectorExtended=false;
        collectorSole1.Set(true);
        collectorSole2.Set(false);
      }
      //}}}
      //Collector Motor{{{
      if(Rstick.GetRawButton(1)==1&&50>=(potToDegrees(armPot.GetAverageVoltage()))){
        setMotorValue(6,1,1);
      }else if(Rstick.GetRawButton(2)==1){
        setMotorValue(6,1,255);
      }else if(shooter_idle==true){
        setMotorValue(6,1,0);
      }
      //}}}
      //}}}
      //Driving{{{
      driveRobot(-Rstick.GetY(),Rstick.GetZ()+Rstick.GetX());
      //printf("GetY: %f, GetX/Z: %f\n", Rstick.GetY()),((Rstick.GetZ()+Rstick.GetX()));
      //}}}
      if(shooter_idle==false){ //Start the shooting sequence by telling the robot the arm needs to complete a shot (and isn't finished yet)
        if(shooter_fired(2)==false){ //Only do this if the shooter hasn't "fired" (in the upwards state)
          shooter_fire(shooter_clear_to_fire(), throttle, upLimit, potToDegrees(armPot.GetAverageVoltage()));
        }
        if(shooter_fired(2)==true){
          //After the shooter has fired, lower the shooter arm then reset the whole shooting sequence
          shooter_lower(-0.1, 47, potToDegrees(armPot.GetAverageVoltage()));
        }
      }
      if(shooter_idle==true){
        //Stop the shooter if it should be idle
        shooter_stop();
      }
      runCompressor(i,100);
      updateDashboard();
      i++;
      Wait(0.005f);
    }
    compressing=false;
    compressor.Stop();
  }
  //}}}
  //Test{{{
  void Test(){
    int i=0;
    while(IsEnabled()&&IsTest()){
      i++;
      Wait(0.005f);
    }
  }
  //}}}
};
START_ROBOT_CLASS(RobotDemo);
