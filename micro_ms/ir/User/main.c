#include "stm32f4xx.h"
#include "uart.h"
#include "encode.h"
#include "delay.h"
#include "led.h"
#include "sysc.h"
#include "motor.h"
#include "buzzer.h"
#include "ir.h"

uint32_t delay_time=0, delay_time_dt=0;
u8 i;
int main(void)
{
	delay_ms(50);
	UART_Config();
	Encode_Init();	
	LED_Init();	
	SYS_Time();
	RC_Time();
	Motor_Init();
	Buzzer_Init();
	IR_ADC_Init();

  printf("OK");

	Motor_Pwm_Flash(0,0,0,0);
	led_s1_on;led_s2_on;
 // Ready_Start();
	delay_ms(50);
	ir_1_on;
	while(ir_adc_1a_value_new < ir_start_value);
	led_s1_off;led_s2_off;
	ir_1_off;
	led_r_on;
	delay_ms(200);
	led_l_off;led_r_off;
	Motor_Pwm_Flash(130,0,100,0);
	//IR_OUT_Mode();
	//Buzzer_Soud(5);
  while(1)
	{ 
		ir_1_off;
		delay_ms(1);
		ir_1_on;
		delay_ms(1);
		
		if(ir_adc_1a_value_new > ir_start_value)
			led_s1_on;
		else
			led_s1_off;
		
		if(ir_adc_2a_value_new > ir_start_value)
			led_s2_on;
		else
			led_s2_off;
		
		if( ir_adc_1a_value_new >ir_start_value_back && ir_adc_2a_value_new > ir_start_value_back)
		{
			while(1)
			{
				delay_ms(1);
				Motor_Pwm_Flash(1,1,1,1);
				delay_ms(1);
				led_s1_on;
				Motor_Pwm_Flash(0,300,0,300);
				delay_ms(3);
				led_s2_on;
				Motor_Pwm_Flash(1,1,1,1);
				delay_ms(5);
				Motor_Pwm_Flash(0,300,300,0);
				delay_ms(18);
				Motor_Pwm_Flash(1,1,1,1);
				delay_ms(1);
				Motor_Pwm_Flash(130,0,100,0);
				delay_ms(20);
				while( ir_adc_1a_value_new <ir_start_value_back && ir_adc_2a_value_new < ir_start_value_back);
				delay_ms(1);
				Motor_Pwm_Flash(1,1,1,1);
				delay_ms(1);
				Motor_Pwm_Flash(0,200,0,200);
				delay_ms(8);
				Motor_Pwm_Flash(1,1,1,1);
				while(1);
			}
		}
		
	 // Motor_Pwm_Flash(0,50,0,50);
//		if( ir_adc_1a_value_new >ir_start_value_back && ir_adc_2a_value_new > ir_start_value_back)
//		{
//				Motor_Pwm_Flash(0,0,0,0);
//			  delay_ms(1);
//		    Motor_Pwm_Flash(0,50,0,50);
//			  delay_ms(1);
//				Motor_Pwm_Flash(0,0,0,0);
//		  	delay_ms(1);
//			  Motor_Pwm_Flash(0,200,200,0);
//			  delay_ms(10);
//			  Motor_Pwm_Flash(0,50,0,50);
//		}
		
//		printf("encode1=%d    ",encode_1_pulse_total/4);
//		printf("encode1=%d  \n",encode_2_pulse_total/4);
//		printf("************");
//		printf("ir_1b=%d   ",ir_adc_1_get[1]);
		
//   		printf("ir_1b=%d    ",ir_adc_1a_value_new/16);
//		  printf("ir_1b=%d    \n",ir_adc_2a_value_new/16);
//		printf("ir_1c=%d    ",ir_adc_1c_value_new);
//		printf("ir_2a=%d   \n",ir_adc_2a_value_new);
	}
	
}

