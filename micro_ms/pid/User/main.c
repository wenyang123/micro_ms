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
int16_t gyrodata[3] = {0};


extern u32 dt_t;
extern float imu_yaw;
extern float imu_dt;

uint16_t  rc_timer_counter=0;
uint8_t rc_timer_state=0;
uint8_t ir_mode_times=0;
uint32_t  aa=0;


IR_Data_X ir_data_1a, ir_data_1b, ir_data_1c;
IR_Data_X ir_data_2a, ir_data_2b, ir_data_2c;
int main(void)
{
	delay_ms(50);
	UART_Config();
	Encode_Init();	
	LED_Init();	
	MPU9250_Mode_Init();
	MPU9250_Mode_LPD2p_Set_Cutoff();
	IR_ADC_Init();
	SYS_Time();
	RC_Time();
	Motor_Init();
	PID_Parameter_Init();
	Buzzer_Init();
	delay_ms(1000);
	Ready_Start_Mode();
	MPU9250_Mode_MeCheck();
	led_f_on;
//	delay_ms(2000);
	led_f_off; led_l_on;
	encode_1_pulse_total = 0; 
	encode_2_pulse_total = 0;
	beeline_speed_desired = beeline_speed_init;
	init_finish = 1;
	//Buzzer_So ud(5);
	//Ready_Start_Mode();
  while(1)
	{ 
		if(loop_rc == 1)
		{
			loop_rc = 0;
			rc_timer_counter++;
			switch(rc_timer_state)
			{
				case waite:
					IR_ADC_Dataup();
					switch(ir_mode_times)
					{
						case ir_a_start: 
							ir_data_1a.ir_adc_value_sys_get = ir_adc_1a_value_new;
        			ir_data_2a.ir_adc_value_sys_get = ir_adc_2a_value_new;
							ir_1_on;ir_2_off;ir_3_off;
							break;
//						case ir_b_start:
//							ir_1_off;ir_2_on;ir_3_off;
//						  ir_adc_1b_value_sysc_get = ir_adc_1b_value_new;
//        			ir_adc_2b_value_sysc_get = ir_adc_2b_value_new;
//							break;
						case ir_c_start:
							ir_data_1c.ir_adc_value_sys_get = ir_adc_1a_value_new;
        			ir_data_2c.ir_adc_value_sys_get = ir_adc_2a_value_new;
							ir_1_off;ir_2_off;ir_3_on;
						
							ir_data_1a.ir_adc_value_sysc_get_dt = ir_adc_1a_value_new - ir_data_1a.ir_adc_value_sys_get;
        			ir_data_2a.ir_adc_value_sysc_get_dt = ir_adc_2a_value_new - ir_data_2a.ir_adc_value_sys_get;
						  if(ir_data_1a.ir_adc_value_sysc_get_dt <= 0 )
								ir_data_1a.ir_adc_value_sysc_get_dt=0;
							if(ir_data_2a.ir_adc_value_sysc_get_dt <= 0 )
								ir_data_2a.ir_adc_value_sysc_get_dt=0;
							
							ir_data_1a.ir_adc_value_get = ir_data_1a.ir_adc_value_sysc_get_dt;
							ir_data_2a.ir_adc_value_get = ir_data_2a.ir_adc_value_sysc_get_dt;
							break;
							
						case ir_b_start:
              ir_1_off;ir_2_off;ir_3_off;

							ir_data_1c.ir_adc_value_sysc_get_dt = ir_adc_1c_value_new - ir_data_1c.ir_adc_value_sys_get;
        			ir_data_2c.ir_adc_value_sysc_get_dt = ir_adc_2c_value_new - ir_data_2c.ir_adc_value_sys_get;
						  if(ir_data_1c.ir_adc_value_sysc_get_dt <= 0 )
								ir_data_1c.ir_adc_value_sysc_get_dt=0;
							if(ir_data_2c.ir_adc_value_sysc_get_dt <= 0 )
								ir_data_2c.ir_adc_value_sysc_get_dt=0;
							
							ir_data_1c.ir_adc_value_get = ir_data_1c.ir_adc_value_sysc_get_dt;
							ir_data_2c.ir_adc_value_get = ir_data_2c.ir_adc_value_sysc_get_dt;
						  
						  ir_data_1c.ir_adc_value_get = ir_adc_1c_value_new;
        			ir_data_2c.ir_adc_value_get = ir_adc_2c_value_new;
						
						default:
							ir_1_off;ir_2_off;ir_3_off;

					}
					if(ir_mode_times == 6) ir_mode_times=0;
					if((rc_timer_counter%5) == 0) rc_timer_state=update_command;
					break;
				
//				case usart_command:
//					STOP_Time++;
//					loopMZCnt_NE=0;
//					USART_UpData();
//					RC_Timer_counter=loopMZCnt_NE;
//					loopMZCnt_NE=0;
//				  RC_timer_state=UPDATE_COMMAND;
//				//  if(STOP_Time==60)RC_timer_state=STOP_COMMAND;
//					break;
				
				case update_command:
					ir_mode_times++;
					loop_rc_times = 0;
					IMU_DataUp();
					Modo_DataUp();
				  delay_ms(1);
				  //aa++;
					//printf("err=%3.2f     v=%3.2f    to=%3.2f    %5d\n", beeline_speed_pid.Error, encode_velocity, BeelineSpeed, aa);
//		      printf("ir_1a=%5d    ir_2b=%5d    ",ir_data_1a.ir_adc_value_get , ir_data_2a.ir_adc_value_get );
//			    printf("ir_1c=%5d    ir_2c=%5d\n",ir_data_1c.ir_adc_value_get , ir_data_2c.ir_adc_value_get );
	
				if( (ir_data_1a.ir_adc_value_get  > ir_start_value_back) && (ir_data_2a.ir_adc_value_get  > ir_start_value_back) ) 
					{
					  rc_timer_state = stop_command;
						break;
				  }
					if( ir_data_1c.ir_adc_value_get  > ir_value_lr) 
						led_s1_on;
					else
						led_s1_off;
					if(ir_data_2c.ir_adc_value_get  > ir_value_lr)  
						led_s2_on;
					else
						led_s2_off;
//				  printf("ir_1a=%5d    ",ir_adc_1a_value_sysc_get);
//    		  printf("ir_1b=%5d    \n",ir_adc_2a_value_sysc_get);
					rc_timer_counter = loop_rc_times;
					rc_timer_state = waite;
				//  if((RC_Timer_counter%46)==0) RC_timer_state=USART_COMMAND;
					break;
				
				case stop_command:
						led_f_on;
				    ir_1_off;ir_2_off;ir_3_off;
						beeline_speed_desired = 0;
						while(encode_velocity > 0)
						{
							Modo_DataUp();
							printf("err=%3.2f     v=%3.2f    to=%3.2f    %5d\n", beeline_speed_pid.Error, encode_velocity, BeelineSpeed, aa);
						}
						Motor_Pwm_Flash(0,0,0,0);
						while(1);
						Motor_Pwm_Flash(0,0,0,0);
						delay_ms(1);
						Motor_Pwm_Flash(0,450,0,450);
						delay_ms(170);
						Motor_Pwm_Flash(0,0,0,0);
						ir_1_off;
						while(1);
					break;
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
}

