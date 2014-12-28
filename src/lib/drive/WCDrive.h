#include <WPILib.h>
class WCDrive {
    private:
        Talon *engine1, *engine2, *engine3, *engine4, *engine5, *engine6;
    public:
        //Assume 4 motors unless otherwise stated
        //motors,pwm1,pwm2,pwm3,pwm4,(pwm5,pwm6)
        explicit WCDrive(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
        //motors,sidecarpwm1,pwm1,sidecarpwm2,pwm2,sidecarpwn3,pwm3,sidecarpwm4,pwm4,(sidecarpwm5,pwm5,sidecarpwm6,pwm6)
        WCDrive(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
        //motor count, x, y
        void Update(int, float,float);
};
