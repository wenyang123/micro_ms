#include "stm32f4xx.h"
#include "uart.h"
#include "encode.h"
#include "delay.h"
#include "led.h"
#include "sysc.h"
#include "motor.h"
#include "buzzer.h"
#include "ir.h"
#include "driver.h"
#include "mpu9250.h"

uint32_t delay_time=0, delay_time_dt=0;
u8 i;
int16_t gyrodata[3] = {0};
u32 gy_time_flag=0;
u32 gy_time_new=0;
float groy_dt=0.0f;
float groy_z=0.0f;

extern u32 dt_t;
int main(void)
{
	delay_ms(50);
	UART_Config();
	Encode_Init();	
	LED_Init();	
	SYS_Time();
	RC_Time();
	MPU9250_Mode_Init();
	MPU9250_Mode_LPD2p_Set_Cutoff();
	Motor_Init();
	Buzzer_Init();
	IR_ADC_Init();
	MPU9250_Mode_MeCheck();
	led_f_off; led_l_on;
	//Buzzer_Soud(5);
	//Ready_Start_Mode();
  while(1)
	{ 

	  ///Test_Dt(&gy_time_flag);
		MPU9250_Mode_DataUp();
		gy_time_new=Test_Dt(&gy_time_flag);
		
		groy_dt = gy_time_new/1000000.0f;
		groy_z += mpu9250.gyroData[2] * groy_dt;
		
//		printf("dt_o=%5d    \n",gy_time_new);
		//printf("dt_o=%5d     o=%3.2f    ",gy_time_new,mpu9250.gyroData[2]);
		printf("gy=%5d    g=%3.2f   \n",mpu9250.gyroADC[2],groy_z);
//		printf("x=%3.2f     y=%3.2f      z=%3.2f \n",mpu9250.gyroData[0],mpu9250.gyroData[1],mpu9250.gyroData[2]);
//		//printf("x=%5d y=%5d, z=%5d \n",mpu9250.gyroData[0],mpu9250.gyroData[1],mpu9250.gyroData[2]);
	}
	
}

