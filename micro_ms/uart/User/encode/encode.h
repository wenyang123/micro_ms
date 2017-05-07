#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "stm32f4xx.h"

#define encode_gpio_rcc_cmd							RCC_AHB1PeriphClockCmd
#define encode_clk_rcc_cmd							RCC_APB1PeriphClockCmd
#define encode_1_clk							      RCC_APB1Periph_TIM2
#define encode_2_clk							      RCC_APB1Periph_TIM3

#define encode_1a_port       						GPIOC   
#define encode_1a_pin             			GPIO_Pin_7                  
#define encode_1a_clk        						RCC_AHB1Periph_GPIOC
#define encode_1a_pinsource							GPIO_PinSource7
#define encode_1a_af								    GPIO_AF_TIM3

#define encode_1b_clk        						RCC_AHB1Periph_GPIOC
#define encode_1b_pin             			GPIO_Pin_6            
#define encode_1b_port       						GPIOC                      
#define encode_1b_pinsource							GPIO_PinSource6
#define encode_1b_af								    GPIO_AF_TIM3

#define encode_2a_clk        						RCC_AHB1Periph_GPIOD
#define encode_2a_pin             			GPIO_Pin_13            
#define encode_2a_port       						GPIOD                      
#define encode_2a_pinsource						  GPIO_PinSource13
#define encode_2a_af								    GPIO_AF_TIM4

#define encode_2b_clk        						RCC_AHB1Periph_GPIOD
#define encode_2b_pin             			GPIO_Pin_12            
#define encode_2b_port       						GPIOD                      
#define encode_2b_pinsource							GPIO_PinSource12
#define encode_2b_af								    GPIO_AF_TIM3


static void Encode_GPIO_Init(void);
void Encode_Init(void);

#endif


