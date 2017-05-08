#ifndef __SYSC_H
#define	__SYSC_H

#include "stm32f4xx.h"

extern uint16_t loop_cnt;
extern uint16_t loop_cnt_cout;

#define sys_time_rcc_cmd	                    RCC_APB1PeriphClockCmd
#define sys_time_clk													RCC_APB1Periph_TIM2
#define sys_time_num          					    	TIM2

#define rc_time_rcc_cmd	                      RCC_APB1PeriphClockCmd
#define rc_time_clk													  RCC_APB1Periph_TIM12
#define rc_time_num          					    	  TIM12
#define rc_time_irqn													TIM8_BRK_TIM12_IRQn

#define RC_TIME_IRQnHandler										TIM8_BRK_TIM12_IRQHandler

#define waite                                 0
#define usart_command                         1
#define update_command                        2
#define stop_command                          3




static void RC_NVIC_Configuration(void);
void SYS_Time(void);
void RC_Time(void);
uint32_t Test_Dt(uint32_t *od_time);
#endif
