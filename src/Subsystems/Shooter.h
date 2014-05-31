#include <WPILib.h>
#include "../Definitions.h"

class ZaphodShooter
{
  private:
    Jaguar *shooterLeft1, *shooterLeft2, *shooterRight1, *shooterRight2;
    AnalogChannel *shooterAngle;     
  public:
    ZaphodShooter();
    enum 
    {
      IDLE_PRESHOT,
      FIRING,
      LOWERING,
      IDLE_POSTSHOT
    }e_ShooterState;
    bool isShooting;
    float shootingPower;
    void startShootingSequence(float);
    void shootForAngle(float, float);
    void shootRaw(float);
    void lower(float);
    void stopShooter();
    void updateShooterPosition();
    float floatToPWM(float input);
    float getAngle();
};
