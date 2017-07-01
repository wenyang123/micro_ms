#include "pid.h"

PID_Typedef yaw_angle_pid;    //yaw角度PID 
PID_Typedef yaw_rate_pid;     //yaw角速率PID
PID_Typedef beeline_speed_pid;		 //直线速度PID

float PID_DataUp(PID_Typedef *PID, float Desired, float Measured, float Dt)
{
    float output;
	  PID->Desired = Desired;
    PID->Error = PID->Desired - Measured;
		
	  if( fabs(PID->Error) < Desired/2)
			PID->Integ += PID->Error * Dt;
    if(PID->Integ > PID->iLimit)
    {
        PID->Integ = PID->iLimit;
    }
    else if(PID->Integ < PID->iLimitLow)
    {
        PID->Integ = PID->iLimitLow;
    }

    PID->Deriv = (PID->Error - PID->PrevError) / Dt;

    PID->outP = PID->Kp * PID->Error;
    PID->outI = PID->Ki * PID->Integ;
    PID->outD = PID->Kd * PID->Deriv;

    output = PID->outP + PID->outI + PID->outD;

    PID->PrevError = PID->Error;

    return output;
}

void PID_Parameter_Config(PID_Typedef *PID, float desired, float kp, float ki, float kd, float PID_LIMIT)
{
  PID->Error = 0;
  PID->PrevError = 0;
  PID->Integ = 0;
  PID->Deriv = 0;
  PID->Desired = desired;
  PID->Kp = kp;
  PID->Ki = ki;
  PID->Kd = kd;
  PID->iLimit = PID_LIMIT;
  PID->iLimitLow = -PID_LIMIT;
}

void PID_Parameter_Init(void)
{
	PID_Parameter_Config(&yaw_angle_pid,0,yaw_angle_PID_P,yaw_angle_PID_I,yaw_angle_PID_D,yaw_angle_PID_iLimit);
	PID_Parameter_Config(&yaw_rate_pid,0,yaw_rate_PID_P,yaw_rate_PID_I,yaw_rate_PID_D,yaw_rate_PID_iLimit);
  PID_Parameter_Config(&beeline_speed_pid,0,beeline_speed_PID_P,beeline_speed_PID_I,beeline_speed_PID_D,beeline_speed_PID_iLimit);

}

void PID_Set_Desired(PID_Typedef *PID, float desired)
{
	  PID->Desired = desired;
}

float PitchRateDesired,RollRateDesired,YawRateDesired;

void PID_Angle_UpData(float eulerYawActual, float eulerYawDesired, float Dt)
{
//  float yawError;
//  yawError = eulerYawDesired - eulerYawActual;
//  if (yawError > 180.0)
//    yawError -= 360.0;
//  else if (yawError < -180.0)
//    yawError += 360.0;
//  pidSetError(&pidYaw, yawError);
  YawRateDesired = PID_DataUp(&yaw_angle_pid,eulerYawDesired,eulerYawActual,Dt);
}


float rollOutput,pitchOutput,yawOutput;
float Pitch,Roll,Yaw;

void PID_Rage_DataUp(float yawRateActual, float yawRateDesired, float Dt)
{
	yawOutput = PID_DataUp(&yaw_rate_pid,yawRateDesired,yawRateActual,Dt);
	Yaw=yawOutput;
}

float BeelineSpeedOutput;
float BeelineSpeed;

void PID_Beeline_Speed_DataUp(float BeelineSpeedActual, float BeelineSpeedDesired, float Dt)
{
	BeelineSpeedOutput = PID_DataUp(&beeline_speed_pid, BeelineSpeedDesired, BeelineSpeedActual, Dt);
	BeelineSpeed = BeelineSpeedOutput;
}




