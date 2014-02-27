//Sonar code
#include "WPILib.h"
#include "SmartDashboard/SmartDashboard.h"
//#include "Command.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>
class RobotDemo : public SimpleRobot
{
  RobotDrive myRobot;
  float potVal, multiplier, servoXState, servoYState, throttle, ServoXJoyPos, ServoYJoyPos;
  int lastToggle;
  int collectorSpeed;
  bool collectorExtended, toggleCollector, shooting, compressing;
  float DownSpeed, downLimit, upLimit;
  //string cmd;
  Joystick Rstick, Lstick;
  Servo Servo1, Servo2;
  Solenoid collectorSole1, collectorSole2;
  DigitalInput pneumaticLS, shootTopLS, shootBottomLS;
  Relay collectorSpike, lightingSpike;
  Compressor compressor;
  Jaguar Left1, Left2, Left3, Right1, Right2, Right3, RightArmMotor1, RightArmMotor2, LeftArmMotor1, LeftArmMotor2, CollectorMotor1;
  AnalogChannel armPot;
  //Ultrasonic
  AnalogChannel BallSonicLeft, BallSonicRight, WallSonicLeft, WallSonicRight;
  DigitalOutput BallLeft, BallRight, WallLeft, WallRight;
  //DigitalInput ballLimit;
public:
  RobotDemo():
    //Limit Switches
    //TODO
    //ballLimit(),
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
    compressor(2, 5, 1, 1),
    //Solenoids
    collectorSole1(1),
    collectorSole2(2),
    //Limit switches
    pneumaticLS(1),
    shootTopLS(2),
    shootBottomLS(3),
    //Driver Motors
    Left1(1, 1),
    Left2(1, 2),
    Left3(1, 3),
    Right1(2, 1),
    Right2(2, 2),
    Right3(2, 3),
    //Servos
    Servo1(1, 7),
    Servo2(1, 8),
    //Spikes
    collectorSpike(2, 7),
    lightingSpike(2, 8),
    //Shooter Motors
    LeftArmMotor1(1, 4),
    LeftArmMotor2(1, 5),
    RightArmMotor1(2, 4),
    RightArmMotor2(2, 5),
    //Collector Motor
    CollectorMotor1(1, 6),
    myRobot(Left1, Left2, Right1, Right2) {
      GetWatchdog().SetEnabled(false);
    }
  void RobotInit() {
    //Initializing robot
    lastToggle = 0;
    DashboardSetup();
    servoXState = 90;
    servoYState = 90;
    multiplier = 1.0f;
    downLimit = 40;
    upLimit = 130;
    compressor.Start();
    shooting = false;
    compressing = true;
    toggleCollector = false;
    throttle=0;
  }
  void DashboardSetup() {
    SmartDashboard::PutNumber("Throttle", throttle);
    SmartDashboard::PutNumber("downLimit", downLimit);
    SmartDashboard::PutNumber("upLimit", upLimit);
    SmartDashboard::PutNumber("DownSpeed", 0.100);
    //SmartDashboard::PutString("Auto", cmd);
    SmartDashboard::PutNumber("collectorSpeed", 127);
    SmartDashboard::PutNumber("armPot", potToDegrees(armPot.GetAverageVoltage()));
    SmartDashboard::PutNumber("Log Level", 1);
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left", voltToDistance(WallSonicLeft.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Wall Right", voltToDistance(WallSonicRight.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Ball Left", voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right", voltToDistance(BallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutBoolean("Use Ultrasonic",false);
    SmartDashboard::PutBoolean("Daniel Mode",false);
  }
  void updateDashboard() {
    SmartDashboard::PutNumber("Throttle", throttle);
    collectorSpeed = SmartDashboard::GetNumber("collectorSpeed");
    SmartDashboard::PutNumber("armPot", potToDegrees(armPot.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Left", voltToDistance(WallSonicLeft.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Wall Right", voltToDistance(WallSonicRight.GetAverageVoltage(),true));
    SmartDashboard::PutNumber("Ball Left", voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right", voltToDistance(BallSonicRight.GetAverageVoltage()));
    DownSpeed = SmartDashboard::GetNumber("DownSpeed");
    downLimit = SmartDashboard::GetNumber("downLimit");
    upLimit = SmartDashboard::GetNumber("upLimit");
    if(downLimit < 35) {
      downLimit = 35;
    }
    if(upLimit > 167) {
      upLimit = 167;
    }
  }
  void shootRobot(float power=0, bool override=false) {
    override=true;
    //Needs a limit to help the driver aim
    //In this case its checking that we are no more than 15 degrees off
    //The override is in place in case an ultrasonic becomes damaged and we are unable to validate the distance through software
    float averageAtan = atan((abs(voltToDistance(BallSonicLeft.GetAverageVoltage()) - voltToDistance(BallSonicRight.GetAverageVoltage())))/20.0f)*360.0f/(2.0f*3.141592653589793f);
    if(override==true) {
      printf("%f\n",power);
      setMotorValue(4, 1, cvt(power));
      setMotorValue(5, 1, cvt(power));
      setMotorValue(4, 2, cvt(-power));
      setMotorValue(5, 2, cvt(-power));
    } else if(averageAtan<=30.0f&&(voltToDistance(WallSonicLeft.GetAverageVoltage(),true))<=100&&(voltToDistance(WallSonicRight.GetAverageVoltage(),true))<=100) {
      setMotorValue(4, 1, cvt(power));
      setMotorValue(5, 1, cvt(power));
      setMotorValue(4, 2, cvt(-power));
      setMotorValue(5, 2, cvt(-power));
    }
    if(averageAtan>=16.0f&&(voltToDistance(WallSonicLeft.GetAverageVoltage(),true))<=100&&(voltToDistance(WallSonicRight.GetAverageVoltage(),true))) {
      //printf/smartdashboard: warning
      setMotorValue(4, 1, cvt(power));
      setMotorValue(5, 1, cvt(power));
      setMotorValue(4, 2, cvt(-power));
      setMotorValue(5, 2, cvt(-power));
    }
    //Allow shooting regardless of the angle or distance
  }
  void logMsg(std::string message, int level) {
    if((int)SmartDashboard::GetNumber("Log Level") % level == 0) {
      printf((message+"\n").c_str());
    }
  }
  void driveRobot(float x, float y) {
    if(y>1.0f) {
      y=1.0f;
    } else if(y!=0.0f&&y<-1.0f) {
      y=-1.0f;
    }
    int leftPower = ((y+x)/2+1)*127+1;
    int rightPower = ((y-x)/2+1)*127+1;
    //logMsg("leftPower: "+toString<int>(leftPower),3);
    //logMsg("rightPower: "+toString<int>(rightPower),3);
    //logMsg("JoyX: "+toString<float>(Rstick.GetX()),3);
    //logMsg("JoyY: "+toString<float>(Rstick.GetY()),3);
    setMotorValue(1, 1, leftPower);
    setMotorValue(2, 1, leftPower);
    setMotorValue(3, 1, leftPower);
    setMotorValue(1, 2, rightPower);
    setMotorValue(2, 2, rightPower);
    setMotorValue(3, 2, rightPower);
  }
  template<typename numbertype> string toString(numbertype a) {
    //TODO
    stringstream ss;
    ss<<a;
    string s = ss.str();
    return s;
  }
  float voltToDistance(float a,bool wall=false) {
    if(wall) {
      return (a / 0.00488f) / 2.54f;
    } else {
      return (a / 0.000976562f) / 25.4f;
    }
  }
  float potToDegrees(float a) {
    float max = -.0003948;
    float min = 5.0245547;
    float b = a - max;
    min = min - max; // ~5.0027
    max = max - max; //=0
    return 300 - ((b + max) * (300 / min));
  }
  int cvt(float input) {
    return input * 127.0f + 128;
  }
  void setMotorValue(int motor, int subwayStation = 1, int value = 127) {
    if(subwayStation == 1) {
      switch(motor) {
          //Drive motors
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
    } else if(subwayStation == 2) {
      switch(motor) {
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
          Servo1.SetAngle(value);
          break;
        case 8:
          Servo2.SetAngle(value);
          break;
        case 9:
          break;
        case 10:
          break;
      }
    }
  }
  void alignRobot() {
    float yoyo = atan((abs(voltToDistance(BallSonicLeft.GetAverageVoltage()) - voltToDistance(BallSonicRight.GetAverageVoltage())))/20.0f)*360.0f/(2.0f*3.141592653589793f);
    SmartDashboard::PutNumber("Distance", yoyo);
  }
  void Test() {
  }
  void Autonomous() {
    myRobot.SetSafetyEnabled(false);
    //cmd = SmartDashboard::GetString("Auto");
    int avgDist;
    int commandIndex=0;
    int i=0;
    int cur=0;
    int averageAmount=5;
    float initalDriveTime=1.4; //The amount of time in seconds that we will drive forward at the start of the match
    float shooterMaxAngle=125; //The maximum angle that the arm can shoot to during all of auto
    float shooterDelay = 4;    //The amount of time in seconds between the inital drive time and the shooter firing
    float shooterDuration = .5;//The amount of time in seconds that the shooter motors will be moving
    shooterDelay = (initalDriveTime*200)+(shooterDelay*4); //Do math to figure out the times to start the shooting
    float sampleCount=12;
    float avgLeft=0;
    float avgRight=0;
    float curDist;
    float thisIsATest;
    compressing=false;
    collectorSole1.Set(false);
    collectorSole2.Set(true);
    WallLeft.Set(1);
    BallLeft.Set(0);
    WallRight.Set(1);
    BallRight.Set(0);
    while(IsEnabled()&&IsAutonomous()) {
      if(SmartDashboard::GetBoolean("Use Ultrasonic")) {
        if(cur<sampleCount) {
          WallLeft.Set(1);
          WallRight.Set(0);
          avgLeft+=voltToDistance(WallSonicLeft.GetAverageVoltage(),true);
        } else if(cur==sampleCount) {
          avgLeft/=12;
        } else if(cur<sampleCount*4&&cur>3*sampleCount) {
          WallLeft.Set(0);
          WallRight.Set(1);
          avgRight+=voltToDistance(WallSonicRight.GetAverageVoltage(),true);
        } else if(cur==sampleCount*4) {
          avgRight/=12;
          thisIsATest=atan((abs(avgLeft-avgRight))/20.0f)*360.0f/(2.0f*3.141592653589793f);
        } else if(cur==sampleCount*6) {
          cur=0;
        }
        if(i>164) {
          SmartDashboard::PutNumber("Tanval", thisIsATest);
        }
      } else {
        if(i<=initalDriveTime*200) {
          driveRobot(1.0f,0.0f);
          //setMotorValue(6, 1, 1);
        } else if(i>shooterDelay&&i<shooterDelay+(shooterDuration*200)&&shooterMaxAngle>=potToDegrees(armPot.GetAverageVoltage())) {
          driveRobot(0, 0);
          shootRobot(1, true);
          setMotorValue(6, 1, 1);
        }
        if(i>480&&i<430+initalDriveTime){
          driveRobot(-1,0);
          //TODO
        } else if(i>430+initalDriveTime/*&&ballLimit.Get()==1*/) {
          driveRobot(-0.6f,0.0f);
          setMotorValue(6, 1, 1);
          //TODO
        } else if(/*ballLimit.Get()==1&&*/i>430+initalDriveTime) {
          driveRobot(1.0f,0.0f);
        }
        if(i>480&&i<480){
          shootRobot(0.25f,true);
        }
      }
      updateDashboard();
      if(i % 100 == 0 && compressing && compressor.GetPressureSwitchValue() == 1) {
        compressor.Stop();
        compressing = false;
        logMsg("Stopping the compressor",2);
      }
      if(i % 100 == 0 && !compressing && compressor.GetPressureSwitchValue() == 0) {
        compressor.Start();
        compressing = true;
        logMsg("Starting the compressor",2);
      }
      Wait(0.005f);
      i++;
      cur++;
    }
    compressing = false;
    compressor.Stop();
  }
  void OperatorControl() {
    myRobot.SetSafetyEnabled(false);
    int i = 0;
    int cur=0;
    bool swap=false;
    collectorSole1.Set(true);
    collectorSole2.Set(false);
    compressing = false;
    logMsg("Starting Teleop",1);
    while(IsEnabled() && IsOperatorControl()) {
      if(cur==50) {
        cur=0;
        WallLeft.Set(swap?1:0);
        BallRight.Set(swap?1:0);
        WallRight.Set(swap?0:1);
        BallRight.Set(swap?0:1);
        swap=!swap;
      }
      throttle = (-Lstick.GetRawAxis(4)+1)/2;
      if(SmartDashboard::GetBoolean("Daniel Mode")) {
        driveRobot(-Rstick.GetY(),Rstick.GetZ()+Rstick.GetX());
      } else {
        driveRobot(Rstick.GetY(),Rstick.GetZ()+Rstick.GetX());
      }
      //Log things
      if(i % 200 == 0) {
        //logMsg(toString(compressor.GetPressureSwitchValue()),2);
        //logMsg("armPot value: "+toString(armPot.GetAverageVoltage(),11));
        //logMsg("Converted armPot value: "+toString(armPot.GetAverageVoltage(),11));
      }
      if(i % 100 == 0 && compressing && compressor.GetPressureSwitchValue() == 1) {
        compressor.Stop();
        compressing = false;
        logMsg("Stopping the compressor",2);
      }
      if(i % 100 == 0 && !compressing && compressor.GetPressureSwitchValue() == 0) {
        compressor.Start();
        compressing = true;
        logMsg("Starting the compressor... again",2);
      }
      updateDashboard();
      if(Lstick.GetRawButton(1)==1&&(upLimit>=potToDegrees(armPot.GetAverageVoltage()))) {
        //Move arm motors based on throttle
        if(collectorExtended == false) {
          shooting = false;
          logMsg("Collector is NOT extended, not going to fire",17);
        }
        if(collectorExtended == true) {
          shooting = true;
          logMsg("Firing",13);
          logMsg("Collector is extended, going to fire",17);
          shootRobot(throttle, false);
          setMotorValue(6, 1, 1);
        }
      } else if(Lstick.GetRawButton(1)==1&&(upLimit<=potToDegrees(armPot.GetAverageVoltage()))) {
        shooting = false;
        logMsg("Stopping shooter motor",13);
        logMsg("Stopping collector motor",17);
        shootRobot(0, true);
      } else if(Lstick.GetRawButton(2)==1) {
        //Reverse the arm motors
        shooting = false;
        if(collectorExtended == false) {
          logMsg("Collector is not extended, not going to fire",17);
        }
        if(collectorExtended == true) {
          shootRobot(-DownSpeed, false);
          logMsg("Collector is extended, going to fire",17);
        }
      } else {
        shooting = false;
        //Stop all motors
        shootRobot(0, true);
      }
      if(Rstick.GetRawButton(9)==1) {
        collectorExtended = true;
        collectorSole1.Set(false);
        collectorSole2.Set(true);
      } else if(Rstick.GetRawButton(10)==1) {
        collectorExtended = false;
        collectorSole1.Set(true);
        collectorSole2.Set(false);
      }
      if(Lstick.GetRawButton(11)==1) {
        setMotorValue(6, 1, 1);
      } else if(Lstick.GetRawButton(12)==1) {
        setMotorValue(6, 1, 255);
      } else if(!shooting) {
        setMotorValue(6, 1, 0);
      }
      cur++;
      i++;
      Wait(0.005f);
    }
  }
};
START_ROBOT_CLASS(RobotDemo);
