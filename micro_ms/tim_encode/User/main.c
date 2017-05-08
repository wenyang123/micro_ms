#include "stm32f4xx.h"
#include "uart.h"
#include "encode.h"
#include "delay.h"
#include "led.h"
#include "sysc.h"

uint32_t delay_time=0, delay_time_dt=0;
int main(void)
{
	delay_ms(50);
	UART_Config();
	Encode_Init();	
	LED_Init();	
	SYS_Time();
	RC_Time();

  printf("OK");
  while(1)
	{
/*************���1msʱ��������*********************/			
		delay_ms(50);
  	printf("times=%d  dr_time=%d  \n",loop_cnt_cout,delay_time_dt);		
/*************���50msʱ��������*********************/				
//	Test_Dt(&delay_time);
//	delay_ms(50);
//	delay_time_dt = Test_Dt(&delay_time);
//	loop_cnt = 0;
//	printf("times=%d  dr_time=%d  \n",loop_cnt_cout,delay_time_dt);
	 
/*************���б����������ʾ*********************/		
//	encode_1_cout = (u16)encode_1_num->CNT;
//	encode_2_cout = (u16)encode_2_num->CNT;
//	printf("encode1=%d    ",encode_1_cout/4);
//	printf("encode1=%d  \n",encode_2_cout/4);
	}
	
}

