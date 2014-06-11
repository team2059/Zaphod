#include "Compressor.h"
HHCompressor::HHCompressor(){
  compressor=new Compressor(COMPRESSOR_GAUGE_SIDECAR, COMPRESSOR_GAUGE, COMPRESSOR_RELAY_SIDECAR, COMPRESSOR_RELAY);
  solenoid1=new Solenoid(COMPRESSOR_SOLENOID_ONE);
  solenoid2=new Solenoid(COMPRESSOR_SOLENOID_TWO);
}
void HHCompressor::compressorSystemPeriodic(){
  switch(e_CollectorSolenoidState){
    case EXTENDED:
      solenoid1->Set(false);
      solenoid2->Set(true);
      break;
    case RETRACTED:
      solenoid1->Set(true);
      solenoid2->Set(false);
      break;
    default:
      break;
  }
  e_CollectorSolenoidState=IDLE;
}
void HHCompressor::startCompressing(){
  compressor->Start();
}
void HHCompressor::stopCompressing(){
  compressor->Stop();
}
void HHCompressor::extendCollector(){
  e_CollectorSolenoidState=EXTENDED;
}
void HHCompressor::retractCollector(){
  e_CollectorSolenoidState=RETRACTED;
}
