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
	led_l_on;;
	//Buzzer_Soud(5);
	//Ready_Start_Mode();
  while(1)
	{ 
		delay_ms(1);
		MPU9250_Mode_Read_Gyro(gyrodata);
		printf("x=%5d y=%5d, z=%5d \n",gyrodata[0],gyrodata[1],gyrodata[2]);
	}
	
}

