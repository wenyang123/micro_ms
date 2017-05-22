#ifndef __MOTOR_H
#define	__MOTOR_H

#include "stm32f4xx.h"


#define motor_gpio_rcc_cmd	                  RCC_APB1PeriphClockCmd
#define motor_clk_rcc_cmd											RCC_APB1PeriphClockCmd 
#define motor_clk                             RCC_APB1Periph_TIM5
#define motor_num         					    			TIM5

#define motor_1_pin             					    GPIO_Pin_1            
#define motor_1_port       								    GPIOA                      
#define motor_1_clk        								    RCC_AHB1Periph_GPIOA
#define motor_1_pinsource							    	  GPIO_PinSource1
#define motor_1_af												    GPIO_AF_TIM5

#define motor_2_pin             					    GPIO_Pin_0            
#define motor_2_port       								    GPIOA                      
#define motor_2_clk        								    RCC_AHB1Periph_GPIOA
#define motor_2_pinsource							    	  GPIO_PinSource0
#define motor_2_af												    GPIO_AF_TIM5

#define motor_3_pin             					    GPIO_Pin_3            
#define motor_3_port       								    GPIOA                      
#define motor_3_clk        								    RCC_AHB1Periph_GPIOA
#define motor_3_pinsource							    	  GPIO_PinSource3
#define motor_3_af												    GPIO_AF_TIM5

#define motor_4_pin             					    GPIO_Pin_2            
#define motor_4_port       								    GPIOA                      
#define motor_4_clk        								    RCC_AHB1Periph_GPIOA
#define motor_4_pinsource							    	  GPIO_PinSource2
#define motor_4_af												    GPIO_AF_TIM5


#define motor_oc_polarity                     TIM_OCPolarity_Low
 
#define motor_1_pwm_cpnfig                    0
#define motor_2_pwm_cpnfig                    0
#define motor_3_pwm_cpnfig                    0
#define motor_4_pwm_cpnfig                    0

#define motor_period													999
#define motor_prescaler												0

#define motor_pwm_max      									  200




static void Motor_GPIO_Config(void);
static void Motor_MODE_Config(void);
void Motor_Init(void);
void Motor_Pwm_Flash(int16_t motor_1_pwm,int16_t motor_2_pwm,int16_t motor_3_pwm,int16_t motor_4_pwm);

#endif
