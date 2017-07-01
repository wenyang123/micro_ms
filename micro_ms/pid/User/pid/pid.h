#ifndef __PID_H
#define	__PID_H

#include "stm32f4xx.h"
#include "mathx.h"

typedef struct
{
		float Kp;
		float Ki;
	  float Kd;
    float outP;
    float outI;
    float outD;
    float Desired;
    float Error;
    float PrevError;
    float Integ;
		float iLimit;
		float iLimitLow;
    float Deriv;
    float Output;
 
}PID_Typedef;

#define    yaw_angle_PID_P 					15    // 20,3.7
#define    yaw_angle_PID_I 					0   //0.2
#define    yaw_angle_PID_D  				0.2
#define    yaw_angle_PID_iLimit  	  300

#define    yaw_rate_PID_P 					1   //20
#define    yaw_rate_PID_I 					0.1
#define    yaw_rate_PID_D  					0.04
#define    yaw_rate_PID_iLimit  		300

#define    beeline_speed_PID_P 						5   //20
#define    beeline_speed_PID_I 						0.1 //1.2
#define    beeline_speed_PID_D  					0.01
#define    beeline_speed_PID_iLimit  			300

extern PID_Typedef yaw_angle_PID;    //yaw角度PID 
extern PID_Typedef yaw_rate_PID;     //yaw角速率PID
extern PID_Typedef beeline_speed_pid;    //yaw角度PID 
extern float PitchRateDesired,RollRateDesired,YawRateDesired;
extern float Pitch,Roll,Yaw;
extern float BeelineSpeed;

float PID_DataUp(PID_Typedef *PID, float Desired, float Measured, float Dt);
void PID_Parameter_Config(PID_Typedef *PID, float desired, float kp, float ki, float kd, float PID_LIMIT);
void PID_Parameter_Init(void);
void PID_Set_Desired(PID_Typedef *PID, float desired);
void PID_Angle_UpData(float eulerYawActual, float eulerYawDesired, float Dt);
void PID_Rage_DataUp(float yawRateActual, float yawRateDesired, float Dt);
void PID_Beeline_Speed_DataUp(float BeelineSpeedActual, float BeelineSpeedDesired, float Dt);

#endif 

