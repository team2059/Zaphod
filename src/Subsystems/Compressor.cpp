#include "Compressor.h"
HHCompressor::HHCompressor(){
  compressor=new Compressor(COMPRESSOR_GAUGE_SIDECAR, COMPRESSOR_GAUGE, COMPRESSOR_RELAY_SIDECAR, COMPRESSOR_RELAY);
  solenoid1=new Solenoid(COMPRESSOR_SOLENOID_ONE);
  solenoid2=new Solenoid(COMPRESSOR_SOLENOID_TWO);
  time(&t);
}
void HHCompressor::CompressorSystemPeriodic(){
  switch(e_CollectorSolenoidState){
    case EXTENDED:
      solenoid1->Set(false);
      solenoid2->Set(true);
      break;
    case RETRACTED:
      solenoid1->Set(true);
      solenoid2->Set(false);
      break;
    case IDLE:
      break;
    default:
      break;
  }
  time_t f;
  time(&f);
  printf("%f",difftime(t,f));
  if(difftime(t,f)>1.0f){
    if(compressor->GetPressureSwitchValue()==1){
      compressor->Start();
    }else{
      compressor->Stop();
    }
    t=clock();
  }
  e_CollectorSolenoidState=IDLE;
}
void HHCompressor::ExtendCollector(){
  e_CollectorSolenoidState=EXTENDED;
}
void HHCompressor::RetractCollector(){
  e_CollectorSolenoidState=RETRACTED;
}
