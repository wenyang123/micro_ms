#include "stm32f4xx.h"
#include "uart.h"
#include "encode.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	delay_ms(50);
	UART_Config();
	Encode_Init();	
	Led_Init();	

  printf("OK");
  while(1)
	{
	  delay_ms(50);
		encode_1_cout = (u16)encode_1_num->CNT;
		encode_2_cout = (u16)encode_2_num->CNT;
		printf("encode1=%d    ",encode_1_cout/4);
		printf("encode1=%d  \n",encode_2_cout/4);
	}
	
}

