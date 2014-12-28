#include "Compressor.h"
AirCompressor::AirCompressor(uint8_t compressorGauge, uint8_t compressorRelay){
  compressor = new Compressor(compressorGauge,compressorRelay);
  timer = new Timer();
  lastTime=0;
  compressing=false;
}
AirCompressor::AirCompressor(uint8_t compressorGaugeSidecar, uint8_t compressorGauge, uint8_t compressorRelaySidecar, uint8_t compressorRelay){
  compressor = new Compressor(compressorGaugeSidecar, compressorGauge, compressorRelaySidecar, compressorRelay);
  timer = new Timer();
  lastTime=0;
  compressing=false;
}
void AirCompressor::CompressorSystemPeriodic(){
  bool compressorEnabled;
  if(timer->Get()-lastTime>=0.5f){
    // Update compressor when current time-last time is more than .5 seconds
    lastTime=timer->Get();
    compressorEnabled=true;
  }
  if(compressorEnabled){
    if(compressing&&compressor->GetPressureSwitchValue()==1){
      // It is compressing, but the pressure is too high
      StopCompressor();
    }else if(!compressing&&compressor->GetPressureSwitchValue()==0){
      // It is not compressing and the pressure isn't too high
      StartCompressor();
    }
  }else{
    if(compressing){
      // If the compressor is not enabled, but it's still compressing
      StopCompressor();
    }
  }
  e_CollectorSolenoidState=IDLE;
}
void AirCompressor::StopCompressor(){
  printf("Stopping compressor\n");
  compressor->Stop();
  compressing=false;
}
void AirCompressor::StartCompressor(){
  printf("Starting compressor\n");
  compressor->Start();
  compressing=true;
}
// vim: ts=2:sw=2:et
