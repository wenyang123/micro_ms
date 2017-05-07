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
		led_l_on;led_r_on;led_f_on;led_s1_on;led_s2_on;led_adc_on;
	}
	
}

