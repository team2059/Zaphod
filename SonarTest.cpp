#include "WPILib.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Command.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>
class RobotDemo : public SimpleRobot
{
  RobotDrive myRobot;
  DigitalOutput out,out2;
  Jaguar Left1,Left2,Right1,Right2;
  AnalogChannel BallSonicLeft,BallSonicRight;
public:
  RobotDemo():
    out(1),
    out2(2),
    Left1(1),
    Left2(2),
    Right1(3),
    Right2(4),
    BallSonicLeft(1),
    BallSonicRight(2),
    myRobot(Left1,Left2,Right1,Right2){
      GetWatchdog().SetEnabled(false);
    }
  void RobotInit(){
    SmartDashboard::PutNumber("Ball Left", voltToDistance(BallSonicLeft.GetAverageVoltage()));
    SmartDashboard::PutNumber("AtanValue", atan((voltToDistance(BallSonicLeft.GetAverageVoltage()) - voltToDistance(BallSonicRight.GetAverageVoltage()))/20.0f)/(2*3.14159265358979)*360);
  }
  void Test(){
    while(IsEnabled()&&IsTest()){
    }
  }
  void Autonomous(){
    myRobot.SetSafetyEnabled(false);
    bool swap=true;
    int i=0;
    int cur=0;
    while(IsEnabled()&&IsAutonomous()){
      if(cur==50){
        cur=0;
        if(swap){
          out.Set(1);
          out2.Set(0);
        }else{
          out.Set(0);
          out2.Set(1);
        }
        printf("Swap: %d\n",swap);
        swap=!swap;
      }
      SmartDashboard::PutNumber("Ball Left", voltToDistance(BallSonicLeft.GetAverageVoltage()));
      SmartDashboard::PutNumber("Ball Right", voltToDistance(BallSonicRight.GetAverageVoltage()));
      SmartDashboard::PutNumber("AtanValue", atan((abs(voltToDistance(BallSonicLeft.GetAverageVoltage()) - voltToDistance(BallSonicRight.GetAverageVoltage())))/20.0f)*360.0f/(2.0f*3.141592653589793f));
      i++;
      cur++;
      Wait(0.005f);
    }
  }
  void OperatorControl(){
  }
  float voltToDistance(float a) {
    return (a / 0.000976562f) / 25.4f;
  }
};
START_ROBOT_CLASS(RobotDemo);
