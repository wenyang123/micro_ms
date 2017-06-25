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
#include "pid.h"

uint32_t delay_time=0, delay_time_dt=0;
u8 i;
int16_t gyrodata[3] = {0};


extern u32 dt_t;
extern float imu_yaw;
extern float imu_dt;

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
	PID_Parameter_Init();
	Buzzer_Init();
	IR_ADC_Init();
	delay_ms(1000);
	Ready_Start_Mode();
	MPU9250_Mode_MeCheck();
	led_f_on;
//	delay_ms(2000);
	led_f_off; led_l_on;
	//Buzzer_So ud(5);
	//Ready_Start_Mode();
  while(1)
	{ 

	  ///Test_Dt(&gy_time_flag);
//		if(mode_dt > 10)
//		{
//			ir_1_off;
//			if(mode_dt > 50 )
//			{
//				mode_dt = 0;
//			}
//		}
//		else
//			ir_1_on;
		
		MPU9250_Mode_DataUp();
		IMU_DataUp();
		Modo_DataUp();
		if( (ir_adc_1a_value_sysc_get > ir_start_value_back) && (ir_adc_2a_value_sysc_get > ir_start_value_back) ) 
		{
//				printf("\n\nir_1a=%5d    ",ir_adc_1a_value_sysc_get);
//		    printf("ir_2a=%5d    \n",ir_adc_2a_value_sysc_get);
			  led_f_on;
				Motor_Pwm_Flash(0,0,0,0);
			  delay_ms(1);
		    Motor_Pwm_Flash(0,400,0,400);
 			  delay_ms(120);
				Motor_Pwm_Flash(0,0,0,0);
			  ir_1_off;
			while(1);
		}

//		printf("dt_o=%5d    \n",gy_time_new);
		//printf("dt_o=%5d     o=%3.2f    ",gy_time_new,mpu9250.gyroData[2]);
//		  printf("ir_1a=%5d    ",ir_adc_2a_value_sysc_get);
//		  printf("ir_1b=%5d    \n",ir_adc_1a_value_sysc_get);
//  	  printf("Data=%5d    gy=%3.2f    g=%3.2f  ",mpu9250.gyroADC[2],Yaw,imu_yaw);
//	   	printf("M1=%5d   M2=%5d    M3=%5d    M4=%5d \n",Motor[0],Motor[1],Motor[2],Motor[3]);
//		printf("x=%3.2f     y=%3.2f      z=%3.2f \n",mpu9250.gyroData[0],mpu9250.gyroData[1],mpu9250.gyroData[2]);
//		//printf("x=%5d y=%5d, z=%5d \n",mpu9250.gyroData[0],mpu9250.gyroData[1],mpu9250.gyroData[2]);
	}
	
}

