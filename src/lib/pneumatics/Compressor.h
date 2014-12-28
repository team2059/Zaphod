#include <WPILib.h>
#include <time.h>
class AirCompressor{
  private:
    Compressor *compressor;
    //Timer used for keeping time?
    Timer *timer;
    double lastTime;
    bool compressing;
  public:
    enum{
      EXTENDED,
      RETRACTED,
      IDLE
    }e_CollectorSolenoidState;
    explicit AirCompressor(uint8_t,uint8_t);
    AirCompressor(uint8_t,uint8_t,uint8_t,uint8_t);
    void CompressorSystemPeriodic();
    void StopCompressor();
    void StartCompressor();
};
// vim: ts=2:sw=2:et
