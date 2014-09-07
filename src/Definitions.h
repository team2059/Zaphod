#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//Sidecar declarations
#define DRIVE_LEFT_SIDECAR      1
#define DRIVE_RIGHT_SIDECAR     2

#define SHOOTER_LEFT_SIDECAR    1
#define SHOOTER_RIGHT_SIDECAR   2

#define COLLECTOR_SIDECAR       1
#define COMPRESSOR_GAUGE_SIDECAR  2
#define COMPRESSOR_RELAY_SIDECAR  1

#define SONAR_LEFT_DIO_SIDECAR  1
#define SONAR_RIGHT_DIO_SIDECAR 2

//Drive motors
#define DRIVE_LEFT_MOTOR_ONE    1
#define DRIVE_LEFT_MOTOR_TWO    2
#define DRIVE_LEFT_MOTOR_THREE  3

#define DRIVE_RIGHT_MOTOR_ONE   1
#define DRIVE_RIGHT_MOTOR_TWO   2
#define DRIVE_RIGHT_MOTOR_THREE 3

//Shooter motors
#define SHOOTER_LEFT_MOTOR_ONE  4
#define SHOOTER_LEFT_MOTOR_TWO  5

#define SHOOTER_RIGHT_MOTOR_ONE 4
#define SHOOTER_RIGHT_MOTOR_TWO 5

//Collector elements (motor, compressor, etc.)

#define COLLECTOR_MOTOR         6
#define COMPRESSOR_GAUGE        5
#define COMPRESSOR_RELAY        3
#define COMPRESSOR_SOLENOID_ONE 1
#define COMPRESSOR_SOLENOID_TWO 2

//Shooter elements (pot, future limit switch, etc)
#define SHOOTER_ANGLE_POT       6

//Ultrasonic (DIO, Analog, etc)
#define SONAR_FRONT_RIGHT_DIO   4
#define SONAR_FRONT_LEFT_DIO    4
#define SONAR_BACK_LEFT_DIO     5
#define SONAR_BACK_RIGHT_DIO    5

#define SONAR_FRONT_RIGHT_ANA   2
#define SONAR_FRONT_LEFT_ANA    1
#define SONAR_BACK_LEFT_ANA     3
#define SONAR_BACK_RIGHT_ANA    4

//Joystick buttons

#define JOYSTICK_RIGHT          1
#define JOYSTICK_LEFT           2

//Static button assignments

#define SHOOTER_FIRE            1
#define COLLECTOR_INTAKE        1
#define COLLECTOR_OUTTAKE       2
#define COLLECTOR_EXTEND        9
#define COLLECTOR_RETRACT       10

//Drive threshold definitions

#define DRIVE_MAX_VALUE_CHANGE  .05
#define DRIVE_SPEED_FALLBACK    2

#endif
// vim: ts=2:sw=2:et
