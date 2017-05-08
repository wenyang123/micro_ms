#include "sysc.h"
#include "uart.h"

uint16_t loop_cnt=0, loop_cnt_cout=0;
uint32_t rc_time=0,  rc_time_dt=0;

void SYS_Time(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  sys_time_rcc_cmd(sys_time_clk, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = 0XFFFFFFFF;       
  TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;	
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

  TIM_TimeBaseStructure.TIM_Period = 999;       
  TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;	
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
		

/*************检测1ms时间间隔测试*********************/				
//		rc_time_dt = Test_Dt(&rc_time);		
//		printf("RC_Dt=%d  \n",rc_time_dt);
		
/*************检测50ms时间间隔测试*********************/			
//		if(loop_cnt == 0)
//		{
//			loop_cnt = 0;
//			loop_cnt_cout ++;	
//		}
//	  loop_cnt = 1;		
  }
}

/*-------------------计时函数-------------------------------------*/
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


