//TODO:
//Vim-like command propmpt thingy
//about line 334
//Auto
//Sonar code
#include "WPILib.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Command.h"
#include <iostream>
#include <math.h>
class RobotDemo : public SimpleRobot
{
  RobotDrive myRobot;
  //Joystick button inputs
  int buttonOneState, buttonTwoState, buttonFiveState, buttonSixState, buttonEightState, buttonSevenState, buttonNineState, buttonTenState, buttonTwelveState, LbuttonOneState, LbuttonTwoState, LbuttonSevenState, LbuttonEightState,LbuttonNineState, LbuttonTenState, LbuttonElevenState, LbuttonTwelveState;
  float potVal,multiplier, servoXState, servoYState, x, y, throttle, ServoXJoyPos, ServoYJoyPos;
  int leftPower, rightPower, cameraMode;
  int cameraPreset, collectorSpeed;
  bool collectorExtended,toggleCollector;
  int lastToggle;
  bool compressorb, compressing;
  float DownSpeed;
  string cmd, debug;
  Joystick Rstick, Lstick;
  Servo Servo1, Servo2;
  Compressor compressor;
  Solenoid collectorSole1, collectorSole2;
  DigitalInput pneumaticLS, shootTopLS, shootBottomLS;
  Relay collectorSpike, lightingSpike;
  Jaguar Left1,Left2,Left3,Right1,Right2,Right3, RightArmMotor1,RightArmMotor2, LeftArmMotor1,LeftArmMotor2,CollectorMotor1;
  //Pot
  AnalogChannel armPot;
  //Ultrasonic
  AnalogChannel BallSonicLeft,BallSonicRight,WallSonicLeft,WallSonicRight;
public:
  RobotDemo():
    //Joysticks
    Rstick(1),
    Lstick(2),
    //Pot
    armPot(5),
    //Ultrasonic
    BallSonicLeft(1),
    BallSonicRight(2),
    WallSonicLeft(3),
    WallSonicRight(4),
    //Compressor
    //compressor(2,3,1,1),
    compressor(2,5,1,1),//Solenoids
    collectorSole1(1),
    collectorSole2(2),
    //Limit switches
    pneumaticLS(1),
    shootTopLS(2),
    shootBottomLS(3),
    //Driver Motors
    Left1(1,1),
    Left2(1,2),
    Left3(1,3),
    Right1(2,1),
    Right2(2,2),
    Right3(2,3),
    //Servos
    Servo1(1,7),
    Servo2(1,8),
    //Spikes
    collectorSpike(2,7),
    lightingSpike(2,8),
    //Shooter Motors
    LeftArmMotor1(1,4),
    LeftArmMotor2(1,5),
    RightArmMotor1(2,4),
    RightArmMotor2(2,5),
    //Collector Motor
    CollectorMotor1(1,6),
    myRobot(Left1,Left2,Right1,Right2) {
    GetWatchdog().SetEnabled(false);
  }
  void RobotInit() {
    //Initializing robot
    lastToggle = 0;
    DashboardSetup();
    cameraMode = 0;
    servoXState = 90;
    servoYState = 90;
    multiplier = 1.0f;
    cameraPreset = 0;
    compressor.Start();
    compressorb = true;
    compressing = true;
    toggleCollector=false;
    debug="";
  }
  void DashboardSetup() {
    SmartDashboard::PutNumber("Throttle", throttle);
    SmartDashboard::PutNumber("DownSpeed", 0.100);
    SmartDashboard::PutString("Auto", cmd);
    SmartDashboard::PutString("Debuggin:", debug);
    SmartDashboard::PutNumber("collectorSpeed",127);
    SmartDashboard::PutNumber("armPot", armPot.GetAverageVoltage()*10000.0f);
    //FOR DA SAMPLE TEXT BOT POT
    //min: 0.04803774
    //max: 0.05024723
    //(#-0.04803774)/0.05024723
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Right",voltToDistance(WallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Left",voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right",voltToDistance(BallSonicRight.GetAverageVoltage()));
  }
  void updateDashboard() {
    SmartDashboard::PutNumber("Throttle", throttle);
    collectorSpeed = SmartDashboard::GetNumber("collectorSpeed");
    SmartDashboard::PutNumber("armPot", armPot.GetAverageVoltage()*10000.0f);
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Right",voltToDistance(WallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Left",voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right",voltToDistance(BallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Tanval",tan((WallSonicLeft.GetAverageVoltage()-WallSonicRight.GetAverageVoltage())/18.0f));
    DownSpeed = SmartDashboard::GetNumber("DownSpeed");
  }
  void buttonUpdate() {
    //Right joystick input
    buttonOneState=Rstick.GetRawButton(1);
    buttonTwoState=Rstick.GetRawButton(2);
    buttonFiveState=Rstick.GetRawButton(5);
    buttonSixState=Rstick.GetRawButton(6);
    buttonSevenState=Rstick.GetRawButton(7);
    buttonEightState=Rstick.GetRawButton(8);
    buttonNineState=Rstick.GetRawButton(9);
    buttonTenState=Rstick.GetRawButton(10);
    buttonTwelveState=Rstick.GetRawButton(12);
    //Left joystick input
    LbuttonOneState=Lstick.GetRawButton(1);
    LbuttonTwoState=Lstick.GetRawButton(2);
    LbuttonSevenState=Lstick.GetRawButton(7);
    LbuttonEightState=Lstick.GetRawButton(8);
    LbuttonNineState=Lstick.GetRawButton(9);
    LbuttonTenState=Lstick.GetRawButton(10);
    LbuttonElevenState=Lstick.GetRawButton(11);
    LbuttonTwelveState=Lstick.GetRawButton(12);
  }
  void getJoystickAxis() {
    y=Rstick.GetX()*multiplier;
    x=-Rstick.GetY()*multiplier;
    throttle=(-Lstick.GetRawAxis(4)+1.0f)/2.0f;
    leftPower=((y+x)/2+1)*127+1;
    rightPower=((y-x)/2+1)*127+1;
  }
  void updateMotors() {
    setMotorValue(1,1,leftPower);
    setMotorValue(2,1,leftPower);
    setMotorValue(3,1,leftPower);
    setMotorValue(1,2,rightPower);
    setMotorValue(2,2,rightPower);
    setMotorValue(3,2,rightPower);
  }
  //camera functions
  void camerafaceManual(int changex,int changey) {
    servoYState=changey;
    servoXState=changex;
    setMotorValue(7,2,servoXState);
    Wait(0.003);
    setMotorValue(8,2,servoYState);
  }
  void cameraReset() {
    servoXState = 90;
    servoYState = 90;
    setMotorValue(7,2,servoXState);
    setMotorValue(8,2,servoYState);
  }
  float voltToDistance(float a) {
    return a/0.00488f/2.54f;
  }
  int cvt(float input) {
    return input*127.0f+128;
  }
  void setDigitalValue(int device,int subwayStation=1,int value=127) {
    if(subwayStation==1) {
      switch(device) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
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
      case 11:
        break;
      case 12:
        break;
      case 13:
        break;
      case 14:
        break;
      default:
        break;
      }
    } else if(subwayStation==2) {
      switch(device) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
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
      case 11:
        break;
      case 12:
        break;
      case 13:
        break;
      case 14:
        break;
      default:
        break;
      }
    }
  }
  void setMotorValue(int motor,int subwayStation=1,int value=127) {
    if(subwayStation==1) {
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
    } else if(subwayStation==2) {
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
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      }
    }
  }
  bool checkSafety() {
    //Some function that will be called to make sure the collector is out before the shooter is raised
    if(collectorExtended == true) {
      debug += "Collector is extended, not going to fire\n";
      return false;
    }
    if(collectorExtended == false) {
      debug += "Collector is NOT extended, going to fire\n";
      return true;
    }
  }
  void alignRobot() {
    float yoyo=atan(voltToDistance(WallSonicLeft.GetAverageVoltage())-voltToDistance(WallSonicRight.GetAverageVoltage()))/18.0f;
    SmartDashboard::PutNumber("Distance", yoyo);
  }
  //Active functions
  void Test() {
    //code for sonar
    int i=0;
    while(IsEnabled()&&IsTest()) {
      i++;
      if(i%250==0) {
        SmartDashboard::PutNumber("armPot", armPot.GetAverageVoltage()*1000.0f);
      }
    }
  }
  void Autonomous() {
    myRobot.SetSafetyEnabled(false);
    compressor.Start();
    cmd=SmartDashboard::GetString("Auto");
    vector<cCommand> cmds = getCommands((std::string)cmd);
    //printf(((std::string)cmd).c_str());
    //10d drive 10 feet
    //10w wait 10 seconds
    //90t turn 90 degrees, yo
    //3c collect ball and retract after 3 seconds
    //255s shoot at power 255
    //3a align robit for 3 seconds (uses ultrasonic to align robit)
    int commandIndex = 0;
    int i = 0;
    while(IsEnabled()&&IsAutonomous()) {
      if(commandIndex < cmds.size()) {
        if(cmds[commandIndex].Function == "d") {
          if(i*1000 < cmds[commandIndex].Amount) {
            setMotorValue(4,1,255);
            setMotorValue(5,1,255);
            setMotorValue(4,2,255);
            setMotorValue(5,2,255);
          } else {
            commandIndex++;
            i=0;
          }
        } else if(cmds[commandIndex].Function == "w") {
          if(!(i*1000 < cmds[commandIndex].Amount)) {
            commandIndex++;
            i=0;
          }
        }
      }
      potVal=420.0f;
      updateDashboard();
      if(compressor.GetPressureSwitchValue()==1) {
        compressor.Stop();
      }
      i++;
      Wait(0.005f);
    }
    compressor.Stop();
  }
  void OperatorControl() {
    myRobot.SetSafetyEnabled(false);
    int i=0;
    collectorSole1.Set(true);
    collectorSole2.Set(false);
    compressor.Start();
    while(IsEnabled()&&IsOperatorControl()) {
      getJoystickAxis();
      //Log things
      if(i%500==0) {
        printf("Throttle values: (%f,%f,%f)\n", throttle,128-(throttle*127.0f),(throttle*127.0f)+128);
        printf("X,Y: (%f,%f)\n", x, y);
        printf("Pitchfork values: (%f,%f)\n", leftPower, rightPower);
      }
      if(compressing && compressor.GetPressureSwitchValue()) {
        compressor.Stop();
        compressing = false;
        printf("Stopping the compressor\n");
      }
      if(!compressing && compressor.GetPressureSwitchValue()==0) {
        compressor.Start();
        compressing=true;
        printf("Starting the compressor again\n");
        Wait(0.05f);
      }
      updateMotors();
      buttonUpdate();
      updateDashboard();
      if(LbuttonSevenState) {
        cameraPreset++;
        if(cameraPreset>3) {
          cameraPreset=0;
        }
        switch(cameraPreset) {
        case 0:
          camerafaceManual(-90,0);
          break;
        case 1:
          camerafaceManual(90,0);
          break;
        case 2:
          camerafaceManual(0,-90);
          break;
        case 3:
          camerafaceManual(0,90);
          break;
        }
        Wait(.0005f);
      }
      if(LbuttonOneState==1) {
        //Move arm motors based on throttle
        if(collectorExtended == false) {
          debug += "Collector is extended, not going to fire\n";
        }
        if(collectorExtended == true) {
          setMotorValue(4,1,cvt(throttle));
          setMotorValue(5,1,cvt(throttle));
          setMotorValue(4,2,cvt(-throttle));
          setMotorValue(5,2,cvt(-throttle));
          debug += "Collector is NOT extended, going to fire\n";
        }
      } else if(LbuttonTwoState==1) {
        //Reverse the arm motors
        if(collectorExtended == false) {
          debug += "Collector is not extended, not going to fire\n";
        }
        if(collectorExtended == true) {
          setMotorValue(4,1,-cvt(DownSpeed));
          setMotorValue(5,1,-cvt(DownSpeed));
          setMotorValue(4,2,cvt(DownSpeed));
          setMotorValue(5,2,cvt(DownSpeed));
          debug += "Collector is  extended, going to fire\n";
        }
      } else {
        //Stop all motors
        setMotorValue(4,1,127);
        setMotorValue(5,1,127);
        setMotorValue(4,2,127);
        setMotorValue(5,2,127);
      }

      if(LbuttonTenState) {
        collectorExtended = true;
        collectorSole1.Set(false);
        collectorSole2.Set(true);

      } else if(LbuttonNineState) {
        collectorExtended = false;
        collectorSole1.Set(true);
        collectorSole2.Set(false);
      }
      if(LbuttonEightState&&i-lastToggle>200) {
        lastToggle=i;
        collectorExtended = !collectorExtended;
        collectorSole1.Set(collectorExtended);
        collectorSole2.Set(!collectorExtended);
        //setMotorValue(6,1,collectorExtended?);
      }
      if(LbuttonElevenState) {
        setMotorValue(6,1,1);
      } else if(LbuttonTwelveState) {
        setMotorValue(6,1,255);
      } else {
        setMotorValue(6,1,0);
      }
      //Camera directions
      camerafaceManual(LbuttonTwelveState-LbuttonElevenState,LbuttonEightState-LbuttonTenState);
      if(LbuttonNineState==1) {
        cameraReset();
      }
      i++;
      Wait(0.005f);
    }
  }
};
START_ROBOT_CLASS(RobotDemo);

