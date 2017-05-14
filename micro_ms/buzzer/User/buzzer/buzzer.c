#include "buzzer.h"

static void Buzzer_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	buzzer_gpio_rcc_cmd(buzzer_gpio_clk, ENABLE); 
  
	GPIO_PinAFConfig(buzzer_port,buzzer_pinsource,buzzer_af); 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = buzzer_pin;
	GPIO_Init(buzzer_port, &GPIO_InitStructure);
}

static void Buzzer_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
  buzzer_clk_rcc_cmd(buzzer_clk, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = buzzer_period;       
  TIM_TimeBaseStructure.TIM_Prescaler = buzzer_prescaler;	
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = buzzer_repetition;	
	TIM_TimeBaseInit(buzzer_num, &TIM_TimeBaseStructure);
	 

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
	TIM_OCInitStructure.TIM_OCPolarity = buzzer_oc_polarity;  
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = buzzer_pwm_config;
	
  Buzzer_OC_Init(buzzer_num, &TIM_OCInitStructure);	
	Buzzer_OC_Preload_Config(buzzer_num, TIM_OCPreload_Enable);

	TIM_Cmd(buzzer_num, ENABLE);	
	TIM_CtrlPWMOutputs(buzzer_num, ENABLE);
}

void Buzzer_Init(void)
{
	Buzzer_GPIO_Config();
	Buzzer_MODE_Config();
}

void Buzzer_Soud(uint32_t time)
{		
     buzzer_num->buzzer_ccr = buzzer_pwm_soud;
		 delay_ms(time);
}

void Buzzer_Stop(void)
{		
     buzzer_num->buzzer_ccr = buzzer_pwm_stop;
}


