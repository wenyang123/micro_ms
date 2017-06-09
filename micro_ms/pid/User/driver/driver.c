#include "driver.h"

uint32_t pid_time=0;
int16_t Motor[4];
float Thro=100;

void Ready_Start_Mode(void)
{
	Motor_Pwm_Flash(0,0,0,0);
	while(encode_1_pulse_total/4 < 500);
	led_s1_on;
	while(encode_2_pulse_total/4 < 500);
	led_s2_on;
	delay_ms(50);
	ir_1_on;
	while(ir_adc_1a_value_new < ir_start_value);
	led_s1_off;led_s2_off;
	ir_1_off;
	led_r_on;
	delay_ms(200);
	led_l_off;led_r_off;
	//Motor_Pwm_Flash(130,0,100,0);
}

void Modo_DataUp(void)
{
	uint32_t now;
	float dt=0.01;

	now=Test_Dt(&pid_time);
	dt=(float)now/1000000.0f;
	dt=(dt>0.03f)?1:dt;

	PID_Angle_UpData(mpu9250.yaw, 0, dt);
	PID_Rage_DataUp(mpu9250.gyroData[2], YawRateDesired, dt);
	
	if(Thro + Yaw > 0)
	{
		Motor[0] = (int16_t)(Thro - Yaw );   
		Motor[1] = 0;   
	}
	else
	{
		Motor[0] = 0 ;
		Motor[1] = (int16_t)(Thro - Yaw ); 
	}
		
	if(Thro + Yaw > 0)
	{
		Motor[2] = (int16_t)(Thro + Yaw );   
		Motor[3] = 0;   
	}
	else
	{
		Motor[2] = 0 ;
		Motor[3] = (int16_t)(Thro + Yaw ); 
	} 
	
	Motor_Pwm_Flash(Motor[0],Motor[1],Motor[2],Motor[3]);  

//  MotorPwmFlash(0,0,0,0);                 
	
}
