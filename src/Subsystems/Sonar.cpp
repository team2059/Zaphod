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
float HHSonar::getInches(const char* from){
  return 10.9f;
}
