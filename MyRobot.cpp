//TODO:
//Auto
//Sonar code
#include "WPILib.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Command.h"
#include <iostream>
#include <math.h>
#include <vector>
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
  bool shooting, compressing;
  float DownSpeed, downLimit, upLimit;
  string cmd;
  Joystick Rstick, Lstick;
  Servo Servo1, Servo2;
  Solenoid collectorSole1, collectorSole2;
  DigitalInput pneumaticLS, shootTopLS, shootBottomLS;
  Relay collectorSpike, lightingSpike;
  Compressor compressor;
  Jaguar Left1,Left2,Left3,Right1,Right2,Right3, RightArmMotor1,RightArmMotor2, LeftArmMotor1,LeftArmMotor2,CollectorMotor1;
  //Pot
  //AnalogChannel armPot;
  AnalogChannel armPot;
  //Ultrasonic
  AnalogChannel BallSonicLeft,BallSonicRight,WallSonicLeft,WallSonicRight;
public:
  RobotDemo():
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
    downLimit = 40;
    upLimit = 130;
    compressor.Start();
    shooting = false;
    compressing = true;
    toggleCollector=false;
  }
  void DashboardSetup() {
    SmartDashboard::PutNumber("Throttle", throttle);
    SmartDashboard::PutNumber("downLimit", downLimit);
    SmartDashboard::PutNumber("upLimit", upLimit);
    SmartDashboard::PutNumber("DownSpeed", 0.100);
    SmartDashboard::PutString("Auto", cmd);
    SmartDashboard::PutNumber("collectorSpeed",127);
    SmartDashboard::PutNumber("armPot", potToDegrees(armPot.GetAverageVoltage()));
    //FOR DA SAMPLE TEXT BOT POT
    //min: 0.04803774
    //max: 0.05024723
    //(#-0.04803774)/0.05024723
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Right",voltToDistance(WallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Left",voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right",voltToDistance(BallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Log Level",1);
  }
  void updateDashboard() {
    SmartDashboard::PutNumber("Throttle", throttle);
    collectorSpeed = SmartDashboard::GetNumber("collectorSpeed");
    SmartDashboard::PutNumber("armPot", potToDegrees(armPot.GetAverageVoltage()));
    //Ultrasonic
    SmartDashboard::PutNumber("Wall Left",voltToDistance(WallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Wall Right",voltToDistance(WallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Left",voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("Ball Right",voltToDistance(BallSonicRight.GetAverageVoltage()));
    SmartDashboard::PutNumber("Tanval",tan((WallSonicLeft.GetAverageVoltage()-WallSonicRight.GetAverageVoltage())/18.0f));
    DownSpeed = SmartDashboard::GetNumber("DownSpeed");
    downLimit = SmartDashboard::GetNumber("downLimit");
    upLimit = SmartDashboard::GetNumber("upLimit");
    if(downLimit < 35){
      downLimit = 35;
    }
    if(upLimit > 167){
      upLimit = 167;
    }
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
  float potToDegrees(float a){ // a 5.024
    float max = -.0003948;
    float min = 5.0245547;
    float b = a-max;
    min = min-max; // ~5.0027
    max=max-max;   //=0
    return 300-((b+max)*(300/min));
  }
  int cvt(float input) {
    return input*127.0f+128;
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
        break;
      case 8:
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
  bool checkSafety() {
    //Some function that will be called to make sure the collector is out before the shooter is raised
    if(collectorExtended == true) {
      if((int)SmartDashboard::GetNumber("Log Level")%17==0){
        printf("Collector is extended, not going to fire\n");
      }
      return false;
    }
    if(collectorExtended == false) {
      if((int)SmartDashboard::GetNumber("Log Level")%17==0){
        printf("Collector is NOT extended, going to fire\n");
      }
      return true;
    }
  }
  void alignRobot() {
    float yoyo=atan(voltToDistance(WallSonicLeft.GetAverageVoltage())-voltToDistance(WallSonicRight.GetAverageVoltage()))/18.0f;
    SmartDashboard::PutNumber("Distance", yoyo);
  }
  void Test() {
  }
  void Autonomous() {
    myRobot.SetSafetyEnabled(false);
    //compressor.Start();
    cmd=SmartDashboard::GetString("Auto");
    //vector<cCommand> cmds = getCommands((std::string)cmd);
    if((int)SmartDashboard::GetNumber("Log Level")%7==0){
      printf(((std::string)cmd).c_str());
    }
    //d-p255-d10;w-t10
    //(10,255)d
    //10d drive 10 feet
    //10w wait 10 seconds
    //90t turn 90 degrees, yo
    //3c collect ball and retract after 3 seconds
    //255s shoot at power 255
    //3a align robit for 3 seconds (uses ultrasonic to align robit)
    int commandIndex = 0;
    int i = 0;
    collectorSole1.Set(true);
    collectorSole2.Set(false);
    compressor.Start();
    while(IsEnabled()&&IsAutonomous()) {
      if(200>i){
        leftPower=1;
        rightPower=255;
      }else if(i==200){
        leftPower=127;
        rightPower=127;
        collectorSole1.Set(false);
        collectorSole2.Set(true);
      }else if(i>600&&120>=potToDegrees(armPot.GetAverageVoltage())){
        leftPower=127;
        rightPower=127;
        setMotorValue(4,1,cvt(1));
        setMotorValue(5,1,cvt(1));
        setMotorValue(4,2,cvt(-1));
        setMotorValue(5,2,cvt(-1));
        setMotorValue(6,1,1);
      }else{
        leftPower=127;
        rightPower=127;
        setMotorValue(4,1,127);
        setMotorValue(5,1,127);
        setMotorValue(4,2,127);
        setMotorValue(5,2,127);
        setMotorValue(6,1,127);
      }
      updateMotors();
      updateDashboard();
      i++;
      if(i%100==0 && compressing && compressor.GetPressureSwitchValue()==1) {
        compressor.Stop();
        compressing = false;
        if((int)SmartDashboard::GetNumber("Log Level")%2==0){
          printf("Stopping the compressor\n");
        }
      }
      if(i%100==0 && !compressing && compressor.GetPressureSwitchValue()==0) {
        compressor.Start();
        compressing=true;
        if((int)SmartDashboard::GetNumber("Log Level")%2==0){
          printf("Starting the compressor again\n");
        }
      }
      Wait(0.005f);
      /*
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
      */
    }
    compressing=false;
    compressor.Stop();
  }
  void OperatorControl() {
    myRobot.SetSafetyEnabled(false);
    int i=0;
    collectorSole1.Set(true);
    collectorSole2.Set(false);
    compressing=false;
    if((int)SmartDashboard::GetNumber("Log Level")%1==0){
      printf("Starting Teleop\n");
    }
    while(IsEnabled()&&IsOperatorControl()) {
      getJoystickAxis();
      //Log things
      if(i%200==0) {
        if((int)SmartDashboard::GetNumber("Log Level")%2==0){
          printf("%d",compressor.GetPressureSwitchValue());
        }
        if((int)SmartDashboard::GetNumber("Log Level")%3==0){
          printf("Throttle values: (%f,%f,%f)\n", throttle,128-(throttle*127.0f),(throttle*127.0f)+128);
          printf("X,Y: (%f,%f)\n", x, y);
          printf("Pitchfork values: (%f,%f)\n", leftPower, rightPower);
        }
        if((int)SmartDashboard::GetNumber("Log Level")%11==0){
          printf("armPot value: %f\n",armPot.GetAverageVoltage());
          printf("Converted armPot value: %f\n",potToDegrees(armPot.GetAverageVoltage()));
        }
      }
      if(i%100==0 && compressing && compressor.GetPressureSwitchValue()==1) {
        compressor.Stop();
        compressing = false;
        if((int)SmartDashboard::GetNumber("Log Level")%2==0){
          printf("Stopping the compressor\n");
        }
      }
      if(i%100==0 && !compressing && compressor.GetPressureSwitchValue()==0) {
        compressor.Start();
        compressing=true;
        if((int)SmartDashboard::GetNumber("Log Level")%2==0){
          printf("Starting the compressor again\n");
        }
      }
      updateMotors();
      buttonUpdate();
      updateDashboard();
      /*
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
      }
      */
      if(LbuttonOneState==1&&upLimit>=potToDegrees(armPot.GetAverageVoltage())) {
        //Move arm motors based on throttle
        if(collectorExtended == false) {
          shooting=false;
          if((int)SmartDashboard::GetNumber("Log Level")%17==0){
            printf("Collector is notextended, not going to fire\n");
          }
        }
        if(collectorExtended == true) {
          shooting = true;
          if((int)SmartDashboard::GetNumber("Log Level")%13==0){
            printf("Firing %d\n",cvt(-throttle));
          }
          if((int)SmartDashboard::GetNumber("Log Level")%17==0){
            printf("Collector is NOT not extended, going to fire\n");
          }
          setMotorValue(4,1,cvt(throttle));
          setMotorValue(5,1,cvt(throttle));
          setMotorValue(4,2,cvt(-throttle));
          setMotorValue(5,2,cvt(-throttle));
          setMotorValue(6,1,1);
        }
      } else if (LbuttonOneState==1&&upLimit<=potToDegrees(armPot.GetAverageVoltage())) {
        shooting = false;
        if((int)SmartDashboard::GetNumber("Log Level")%13==0){
          printf("Stopping Shooter Motor\n");
        }
        if((int)SmartDashboard::GetNumber("Log Level")%17==0){
          printf("Stopping Collector Motor");
        }
        setMotorValue(4,1,127);//arms
        setMotorValue(5,1,127);
        setMotorValue(4,2,127);
        setMotorValue(5,2,127);
      } else if(LbuttonTwoState==1) {
        //Reverse the arm motors
        shooting = false;
        if(collectorExtended == false) {
          if((int)SmartDashboard::GetNumber("Log Level")%17==0){
            printf("Collector is not extended, not going to fire\n");
          }
        }
        if (collectorExtended == true) {
          setMotorValue(4,1,cvt(-DownSpeed));
          setMotorValue(5,1,cvt(-DownSpeed));
          setMotorValue(4,2,cvt(DownSpeed));
          setMotorValue(5,2,cvt(DownSpeed));
          if((int)SmartDashboard::GetNumber("Log Level")%17==0){
            printf("Collector is  extended, going to fire\n");
          }
        }
      } else {
        shooting=false;
        //Stop all motors
        setMotorValue(4,1,127);
        setMotorValue(5,1,127);
        setMotorValue(4,2,127);
        setMotorValue(5,2,127);
      }
      if(buttonNineState) {
        collectorExtended = true;
        collectorSole1.Set(false);
        collectorSole2.Set(true);
      } else if(buttonTenState) {
        collectorExtended = false;
        collectorSole1.Set(true);
        collectorSole2.Set(false);
      }
      if(LbuttonElevenState) {
        setMotorValue(6,1,1);
      } else if(LbuttonTwelveState) {
        setMotorValue(6,1,255);
      } else if(!shooting){
        setMotorValue(6,1,127);
      }
      //Camera directions
      camerafaceManual(LbuttonTwelveState-LbuttonElevenState,LbuttonEightState-LbuttonTenState);
      if(buttonNineState==1) {
        //cameraReset();
      }
      i++;
      Wait(0.005f);
    }
  }
};
START_ROBOT_CLASS(RobotDemo);
