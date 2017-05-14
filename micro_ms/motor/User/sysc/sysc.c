#include "sysc.h"
#include "uart.h"
#include "encode.h"

uint16_t loop_cnt=0, loop_cnt_cout=0;

void SYS_Time(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  sys_time_rcc_cmd(sys_time_clk, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = sys_time_period;       
  TIM_TimeBaseStructure.TIM_Prescaler = sys_time_Prescaler;	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(sys_time_num, &TIM_TimeBaseStructure);

	TIM_SetCounter(sys_time_num, 0);
	TIM_Cmd(sys_time_num,ENABLE);	
}

void RC_Time(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  rc_time_rcc_cmd(rc_time_clk, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = rc_time_period;       
  TIM_TimeBaseStructure.TIM_Prescaler = rc_time_Prescaler;	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(rc_time_num, &TIM_TimeBaseStructure);

	RC_NVIC_Configuration();
	TIM_ITConfig(rc_time_num, TIM_IT_Update, ENABLE);
	TIM_SetCounter(rc_time_num, 0);
	TIM_Cmd(rc_time_num, ENABLE);	
}

static void RC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
	NVIC_InitStructure.NVIC_IRQChannel = rc_time_irqn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void RC_TIME_IRQnHandler(void)
{
	if (TIM_GetITStatus(rc_time_num, TIM_IT_Update) != RESET)
  {	 
	  TIM_ClearITPendingBit(rc_time_num, TIM_FLAG_Update);
		Encode_Velocity_Get();
  }
}

/*-------------------¼ÆÊ±º¯Êý-------------------------------------*/
uint32_t Test_Dt(uint32_t *od_time)
{
	uint32_t now_time=0, last_time=0;
	
	now_time = TIM_GetCounter(sys_time_num);
	last_time =* od_time;
	*od_time = now_time;
	if(now_time < *od_time)
	{
		now_time = 0xffffffff - *od_time + now_time;
	}
	else
		now_time -= last_time;

	return now_time;
}


