#include <WPILib.h>
#include "../Definitions.h"
#include <time.h>
class HHCompressor{
  private:
    Compressor *compressor;
    Solenoid *solenoid1, *solenoid2;
  public:
    enum{
      EXTENDED,
      RETRACTED,
      IDLE
    }e_CollectorSolenoidState;
    HHCompressor();
    void CompressorSystemPeriodic(bool compressorEnabled);
    void ExtendCollector();
    void RetractCollector();
};
// vim: ts=2:sw=2:et
