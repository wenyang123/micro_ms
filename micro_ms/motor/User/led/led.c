#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	led_gpio_rcc_cmd(led_l_clk|led_r_clk|led_f_clk|led_s1_clk|led_s2_clk|led_adc_clk, ENABLE); 
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = led_l_pin;
	GPIO_Init(led_l_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = led_r_pin;
	GPIO_Init(led_r_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = led_f_pin;
	GPIO_Init(led_f_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = led_s1_pin;
	GPIO_Init(led_s1_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = led_s2_pin;
	GPIO_Init(led_s2_port, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin = led_adc_pin;
	GPIO_Init(led_adc_port, &GPIO_InitStructure);
	
	//led_l_off;led_r_off;led_f_off;led_s1_off;led_s2_off;led_adc_off;
	led_l_on;led_r_on;led_f_on;led_s1_on;led_s2_on;led_adc_on;
}

