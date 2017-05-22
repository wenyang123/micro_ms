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

extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal; 
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
	Rheostat_Init();

  printf("OK");
	
	Motor_Pwm_Flash(0,0,0,0);
  //IR_OUT_Mode();
  // Buzzer_Soud(5);
  while(1)
	{ 
		delay_ms(50);
		 ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*(float)3.3/16.0; // 读取转换的AD值
      printf(" 1= %d   ", ADC_ConvertedValue); 
      printf(" 2=%f V \r\n",ADC_ConvertedValueLocal); 

//		printf("encode1=%d    ",encode_1_pulse_total/4);
//		printf("encode1=%d  \n",encode_2_pulse_total/4);
//  		printf("ir_1a=%d    ",ir_adc_1a_value_new);
//			printf("ir_1a=%0.2f    \n",ir_adc_1a_value_new/1.0/4095.0*3.3);
//		printf("ir_1b=%d    ",ir_adc_1b_value_new);
//		printf("ir_1c=%d    ",ir_adc_1c_value_new);
//		printf("ir_2a=%d   \n",ir_adc_2a_value_new);
	}
	
}

