#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     carrot,         sensorSONAR)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C2_1,     driveRearRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     driveFrontRight, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     shoulder,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     driveFrontLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     driveRearLeft, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    brush,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_3,    arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    dockarm,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    rightEye,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    leftEye,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    finger,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    door,                 tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define UPCOUNTS      4208
#define LSERVO_CENTER 134
#define RSERVO_CENTER 113
#define RSERVO_PERP   235

#define SERVO_ARM_EXTENDED          85
#define SERVO_ARM_RETRACTED         170
#define SERVO_ARM_EXTENDED_HALF     120
#define SERVO_ARM_PICKUP            160

#define SHOULDER_POWER 80

#define SERVO_DOOR_OPEN             103
#define SERVO_DOOR_CENTERGOAL_RAMP  21
#define SERVO_DOOR_CLOSED           45

#define SERVO_DOCK_ARM_FORWARD      80
#define SERVO_DOCK_ARM_BACKWARD     147
#define SERVO_DOCK_ARM_STOPPED      127
#define SERVO_FINGER_UP             15
#define SERVO_FINGER_DOWN           127
#define FOUR_WHEEL_DRIVE

#include "../../lib/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../../lib/drivetrain_andymark_defs.h"
#include "../../lib/drivetrain_square.h"
#include "../../lib/dead_reckon.h"
#include "../../lib/data_log.h"

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define UPCOUNTS      4000
#define LSERVO_CENTER 134
#define RSERVO_CENTER 113
#define RSERVO_PERP   235

#include "../../lib/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../../lib/baemax_drivetrain_defs.h"
#include "../../lib/drivetrain_square.h"
#include "../../lib/dead_reckon.h"
#include "../../lib/data_log.h"
#include "../../lib/ir_utils.h"

task ext_dock_arm()
{
    servo[dockarm] = SERVO_DOCK_ARM_FORWARD;
    wait1Msec(2000);
    servo[finger] = SERVO_FINGER_UP;
    wait1Msec(1500);
    servo[dockarm] = SERVO_DOCK_ARM_STOPPED;
}

void initializeRobot()
{
    servo[arm] = SERVO_ARM_RETRACTED;
    servo[finger] = SERVO_FINGER_DOWN;
    nMotorEncoder(shoulder) = 0;
    servo[brush] = 127;
    servo[door] = SERVO_DOOR_CLOSED;
}

task main()
{
    initializeRobot();

    waitForStart(); // Wait for the beginning of autonomous phase.

    init_path();
    add_segment(-83, 0, 30);  //gets off the ramp to medium goal
    stop_path();
    dead_reckon();

    while (nMotorEncoder(shoulder) < UPCOUNTS) {
        motor[shoulder] = 15;
    }
    motor[shoulder] = 0;
    servo[door] = SERVO_DOOR_OPEN;
    servo[brush] = 255;
    wait1Msec(4000);
    servo[brush] = 127;

    while (true){
    }
}
