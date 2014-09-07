#include <WPILib.h>
#include "../Definitions.h"
class HHSonar{
  private:
    DigitalOutput *frontLeftD,*frontRightD,*backLeftD,*backRightD;
    AnalogChannel *frontLeftA,*frontRightA,*backLeftA,*backRightA;
  public:
    HHSonar();
    //from is (in string form) "FRONT", "BACK", "FRONTLEFT", "FRONTRIGHT"...
    float GetInches(std::string from);
};
// vim: ts=2:sw=2:et
