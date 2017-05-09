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
		delay_ms(50);
		printf("encode1=%d    ",encode_1_pulse_total/4);
		printf("encode1=%d  \n",encode_2_pulse_total/4);
	}
	
}

