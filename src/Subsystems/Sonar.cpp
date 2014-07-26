#include "Sonar.h"
HHSonar::HHSonar(){
  DigitalOutput frontLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR,SONAR_FRONT_LEFT_DIO);
  DigitalOutput frontRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR,SONAR_FRONT_RIGHT_DIO);
  DigitalOutput backLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR,SONAR_BACK_LEFT_DIO);
  DigitalOutput backRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR,SONAR_BACK_RIGHT_DIO);
  AnalogChannel frontLeftA=new AnalogChannel(SONAR_FRONT_LEFT_ANA);
  AnalogChannel frontRightA=new AnalogChannel(SONAR_FRONT_RIGHT_ANA);
  AnalogChannel backLeftA=new AnalogChannel(SONAR_BACK_LEFT_ANA);
  AnalogChannel backRightA=new AnalogChannel(SONAR_BACK_RIGHT_ANA);
}
float HHSonar::GetInches(std::string from){
  switch(from){
    case "FRONT":
      frontLeftD->Set(1);
      float x=(frontLeftA->GetAverageVoltage()/0.00488f)/2.54f;
      frontLeftD->Set(0);
      //TODO: Delay
      frontRightD->Set(1);
      float y=(frontRightA->GetAverageVoltage()/0.00488f)/2.54f;
      frontRightD->Set(0);
      //TODO: Delay
      return (x+y)/2;
      break;
    case "BACK":
      backLeftD->Set(1);
      float x=(backLeftA->GetAverageVoltage()/0.00488f)/2.54f;
      backLeftD->Set(0);
      //TODO: Delay
      backRightD->Set(1);
      float y=(backRightA->GetAverageVoltage()/0.00488f)/2.54f;
      backRightD->Set(0);
      //TODO: Delay
      return (x+y)/2;
      break;
    case "FRONTLEFT":
      frontLeftD->Set(1);
      float x=(frontLeftA->GetAverageVoltage()/0.00488f)/2.54f;
      frontLeftD->Set(0);
      //TODO: Delay
      return x;
      break;
    case "FRONTRIGHT":
      frontRightD->Set(1);
      float x=(frontRightA->GetAverageVoltage()/0.00488f)/2.54f;
      frontRightD->Set(0);
      //TODO: Delay
      return x;
      break;
    case "BACKLEFT":
      backLeftD->Set(1);
      float x=(backLeftA->GetAverageVoltage()/0.00488f)/2.54f;
      backLeftD->Set(0);
      //TODO: Delay
      return x;
      break;
    case "BACKRIGHT":
      backRightD->Set(1);
      float x=(backRightA->GetAverageVoltage()/0.00488f)/2.54f;
      backRightD->Set(0);
      //TODO: Delay
      return x;
      break;
    default:
      break;
  }
}
