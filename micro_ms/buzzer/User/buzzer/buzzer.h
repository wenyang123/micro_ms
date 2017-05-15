#ifndef __BUZZER_H
#define	__BUZZER_H

#include "stm32f4xx.h"
#include "delay.h"

 //PA0--TIM5_CH1,  PA1--TIM2_CH2

#define buzzer_gpio_rcc_cmd										RCC_AHB1PeriphClockCmd
#define buzzer_clk_rcc_cmd							      RCC_APB2PeriphClockCmd
#define buzzer_clk							     				  RCC_APB2Periph_TIM1
#define buzzer_num												  	TIM1

#define buzzer_port       										GPIOE  
#define buzzer_pin             								GPIO_Pin_14                  
#define buzzer_pinsource											GPIO_PinSource14
#define buzzer_gpio_clk												RCC_AHB1Periph_GPIOE
#define buzzer_af								   						GPIO_AF_TIM1 
#define buzzer_ccr														CCR4		

#define buzzer_oc_polarity               		  TIM_OCPolarity_High

#define buzzer_period													90
#define buzzer_prescaler											60 - 1   //60
#define buzzer_repetition											0
#define buzzer_pwm_config											0
 
#define buzzer_pwm_max      									900

#define buzzer_pwm_soud												45
#define buzzer_pwm_stop												0

#define Buzzer_OC_Init(a,b)  									TIM_OC4Init(a,b);	
#define Buzzer_OC_Preload_Config(a,b) 	      TIM_OC4PreloadConfig(a,b);
				




static void Buzzer_GPIO_Config(void);
static void Buzzer_MODE_Config(void);
void Buzzer_Init(void);
void Buzzer_Soud(uint32_t time);

#endif
