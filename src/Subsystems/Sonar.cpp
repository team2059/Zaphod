#include "Sonar.h"
HHSonar::HHSonar(){
  frontLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR,SONAR_FRONT_LEFT_DIO);
  frontRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR,SONAR_FRONT_RIGHT_DIO);
  backLeftD=new DigitalOutput(SONAR_LEFT_DIO_SIDECAR,SONAR_BACK_LEFT_DIO);
  backRightD=new DigitalOutput(SONAR_RIGHT_DIO_SIDECAR,SONAR_BACK_RIGHT_DIO);
  frontLeftA=new AnalogChannel(SONAR_FRONT_LEFT_ANA);
  frontRightA=new AnalogChannel(SONAR_FRONT_RIGHT_ANA);
  backLeftA=new AnalogChannel(SONAR_BACK_LEFT_ANA);
  backRightA=new AnalogChannel(SONAR_BACK_RIGHT_ANA);
}
float HHSonar::GetInches(std::string from){
  if(from=="FRONT"){
    frontLeftD->Set(1);
    float x=(frontLeftA->GetAverageVoltage()/0.00488f)/2.54f;
    frontLeftD->Set(0);
    //TODO: Delay
    frontRightD->Set(1);
    float y=(frontRightA->GetAverageVoltage()/0.00488f)/2.54f;
    frontRightD->Set(0);
    //TODO: Delay
    return (x+y)/2;
  }else if(from=="BACK"){
    backLeftD->Set(1);
    float x=(backLeftA->GetAverageVoltage()/0.00488f)/2.54f;
    backLeftD->Set(0);
    //TODO: Delay
    backRightD->Set(1);
    float y=(backRightA->GetAverageVoltage()/0.00488f)/2.54f;
    backRightD->Set(0);
    //TODO: Delay
    return (x+y)/2;
  }else if(from=="FRONTLEFT"){
    frontLeftD->Set(1);
    float x=(frontLeftA->GetAverageVoltage()/0.00488f)/2.54f;
    frontLeftD->Set(0);
    //TODO: Delay
    return x;
  }else if(from=="FRONTRIGHT"){
    frontRightD->Set(1);
    float x=(frontRightA->GetAverageVoltage()/0.00488f)/2.54f;
    frontRightD->Set(0);
    //TODO: Delay
    return x;
  }else if(from=="BACKLEFT"){
    backLeftD->Set(1);
    float x=(backLeftA->GetAverageVoltage()/0.00488f)/2.54f;
    backLeftD->Set(0);
    //TODO: Delay
    return x;
  }else if(from=="BACKRIGHT"){
    backRightD->Set(1);
    float x=(backRightA->GetAverageVoltage()/0.00488f)/2.54f;
    backRightD->Set(0);
    //TODO: Delay
    return x;
  }else{
    return (float)(-1);
  }
}
