#include "Compressor.h"
HHCompressor::HHCompressor(){
  compressor=new Compressor(COMPRESSOR_GAUGE_SIDECAR, COMPRESSOR_GAUGE, COMPRESSOR_RELAY_SIDECAR, COMPRESSOR_RELAY);
  solenoid1=new Solenoid(COMPRESSOR_SOLENOID_ONE);
  solenoid2=new Solenoid(COMPRESSOR_SOLENOID_TWO);
  compressing=false;
}
void HHCompressor::CompressorSystemPeriodic(bool compressorEnabled){
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
  if(compressorEnabled){
    printf("Compressor is enabled\n");
    if(compressing&&compressor->GetPressureSwitchValue()==1){
      // It is compressing, but the pressure is too high 
      printf("Condition 1");
      StopCompressor();
    }else if(!compressing&&compressor->GetPressureSwitchValue()==0){
      // It is not compressing and the pressure isn't too high
      printf("Condition 2");
      StartCompressor();
    }
  }else{
    printf("Condition 3");
    if(compressing){
      // If the compressor is not enabled, but it's still compressing
      printf("Condition 4");
      StopCompressor();
    }
  }
  e_CollectorSolenoidState=IDLE;
}
void HHCompressor::ExtendCollector(){
  e_CollectorSolenoidState=EXTENDED;
}
void HHCompressor::RetractCollector(){
  e_CollectorSolenoidState=RETRACTED;
}
void HHCompressor::StopCompressor(){
  printf("Stopping compressor\n");
  compressor->Stop();
  compressing=false;
}
void HHCompressor::StartCompressor(){
  printf("Starting compressor\n");
  compressor->Start();
  compressing=true;
}
// vim: ts=2:sw=2:et
