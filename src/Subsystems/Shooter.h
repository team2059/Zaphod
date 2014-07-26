#include <WPILib.h>
#include "../Definitions.h"
class HHShooter{
  private:
    Jaguar*shooterLeft1, *shooterLeft2, *shooterRight1, *shooterRight2;
    AnalogChannel*shooterAngle;
  public:
    HHShooter();
    enum {
      IDLE_PRESHOT,
      FIRING,
      LOWERING,
      IDLE_POSTSHOT
    }e_ShooterState;
    bool isShooting;
    float shootingPower;
    void StartShootingSequence(float);
    void ShootForAngle(float, float);
    void ShootRaw(float);
    void Lower(float);
    void StopShooter();
    void UpdateShooterPosition();
    float FloatToPWM(float input);
    float GetAngle();
};
