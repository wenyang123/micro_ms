#ifndef __LED_H_
#define __LED_H_

#include "stm32f4xx.h"

#define led_gpio_rcc_cmd							  RCC_AHB1PeriphClockCmd

#define led_l_port       						    GPIOB  
#define led_l_pin             			    GPIO_Pin_0                  
#define led_l_clk        						    RCC_AHB1Periph_GPIOB
#define led_l_def  			  							led_l_port->ODR ^= led_l_pin
#define led_l_on    										led_l_port->BSRRL = led_l_pin
#define led_l_off  			   							led_l_port->BSRRH = led_l_pin
 
#define led_r_port       						    GPIOE   
#define led_r_pin             			    GPIO_Pin_4                  
#define led_r_clk        						    RCC_AHB1Periph_GPIOE
#define led_r_def  			  							led_r_port->ODR ^= led_r_pin
#define led_r_on    										led_r_port->BSRRL = led_r_pin
#define led_r_off  			   							led_r_port->BSRRH = led_r_pin

#define led_f_port       						    GPIOE   
#define led_f_pin             			    GPIO_Pin_5                  
#define led_f_clk        						    RCC_AHB1Periph_GPIOE
#define led_f_def  			  							led_f_port->ODR ^= led_f_pin
#define led_f_on    										led_f_port->BSRRL = led_f_pin
#define led_f_off  			   							led_f_port->BSRRH = led_f_pin

#define led_s1_port       						  GPIOB   
#define led_s1_pin             			    GPIO_Pin_12                  
#define led_s1_clk        						  RCC_AHB1Periph_GPIOB
#define led_s1_def  			  						led_s1_port->ODR ^= led_s1_pin
#define led_s1_on    										led_s1_port->BSRRL = led_s1_pin
#define led_s1_off  			   						led_s1_port->BSRRH = led_s1_pin

#define led_s2_port       						  GPIOD   
#define led_s2_pin             			    GPIO_Pin_2                  
#define led_s2_clk        						  RCC_AHB1Periph_GPIOD
#define led_s2_def  			  						led_s2_port->ODR ^= led_s2_pin
#define led_s2_on    										led_s2_port->BSRRL = led_s2_pin
#define led_s2_off  			   						led_s2_port->BSRRH = led_s2_pin

#define led_adc_port       						  GPIOD   
#define led_adc_pin             			  GPIO_Pin_9                  
#define led_adc_clk        						  RCC_AHB1Periph_GPIOD
#define led_adc_def  			  						led_adc_port->ODR ^= led_adc_pin
#define led_adc_on    									led_adc_port->BSRRL = led_adc_pin
#define led_adc_off  			   						led_adc_port->BSRRH = led_adc_pin

void LED_Init(void);
	
#endif
