#include "WCDrive.h"
//Constructor for drive with 4-6 motors all on first sidecar
WCDrive::WCDrive(uint8_t motorCount, uint8_t motor1, uint8_t motor2, uint8_t motor3, uint8_t motor4, uint8_t motor5=NULL, uint8_t motor6=NULL){
    engine1 = new Talon(motor1);
    engine2 = new Talon(motor2);
    engine3 = new Talon(motor3);
    engine4 = new Talon(motor4);
    if(motorCount==6){
        engine5 = new Talon(motor5);
        engine6 = new Talon(motor6);
    }
}
WCDrive::WCDrive(uint8_t motorCount, uint8_t motor1sidecar, uint8_t motor1, uint8_t motor2sidecar, uint8_t motor2, uint8_t motor3sidecar, uint8_t motor3, uint8_t motor4sidecar, uint8_t motor4, uint8_t motor5sidecar=NULL, uint8_t motor5=NULL, uint8_t motor6sidecar=NULL, uint8_t motor6=NULL){
    engine1 = new Talon(motor1sidecar,motor1);
    engine2 = new Talon(motor2sidecar,motor2);
    engine3 = new Talon(motor3sidecar,motor3);
    engine4 = new Talon(motor4sidecar,motor4);
    if(motorCount==6){
        engine5 = new Talon(motor5sidecar,motor5);
        engine6 = new Talon(motor6sidecar,motor6);
    }
}
void WCDrive::Update(int motorCount, float y, float x){
  if(y>1.0f){
    y=1.0f;
  }else if(y!=0.0f&&y<-1.0f){
    y=-1.0f;
  }
  float leftPower=((y-x)/2+1)*127+1;
  float rightPower=((y+x)/2+1)*127+1;
  engine1->SetRaw(int(rightPower));
  engine2->SetRaw(int(rightPower));
  engine3->SetRaw(int(rightPower));
  engine4->SetRaw(int(leftPower));
  if(motorCount==6){
      engine5->SetRaw(int(leftPower));
      engine6->SetRaw(int(leftPower));
  }
}
