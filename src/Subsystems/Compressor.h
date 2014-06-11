#include <WPILib.h>
#include "../Definitions.h"

class HHCompressor
{
  private:
    Compressor *compressor;
    Solenoid *solenoid1, *solenoid2;
  public:
    enum
    {
      EXTENDED,
      RETRACTED,
      IDLE
    }e_CollectorSolenoidState;
    HHCompressor();
    void compressorSystemPeriodic();
    void ExtendCollector();
    void RetractCollector();
    void StartCompressing();
    void StopCompressing();
};
