#include "motor.h"


static void Motor_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	motor_gpio_rcc_cmd (motor_1_clk|motor_2_clk|motor_3_clk|motor_4_clk, ENABLE); 
  
	GPIO_PinAFConfig(motor_1_port, motor_1_pinsource, motor_1_af); 
	GPIO_PinAFConfig(motor_2_port, motor_2_pinsource, motor_2_af);
	GPIO_PinAFConfig(motor_3_port, motor_3_pinsource, motor_3_af);
	GPIO_PinAFConfig(motor_4_port, motor_4_pinsource, motor_4_af);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = motor_1_pin;
	GPIO_Init(motor_1_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = motor_2_pin;
	GPIO_Init(motor_2_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = motor_3_pin;
	GPIO_Init(motor_3_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = motor_4_pin;
	GPIO_Init(motor_4_port, &GPIO_InitStructure);
}


//--------------------------配置PWM--------------------------------//
static void Motor_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef        TIM_OCInitStructure;
	
  motor_clk_rcc_cmd(motor_clk, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = motor_period;       
  TIM_TimeBaseStructure.TIM_Prescaler = motor_prescaler;	
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(motor_num, &TIM_TimeBaseStructure);
	 
	/*PWM模式配置*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
	TIM_OCInitStructure.TIM_OCPolarity = motor_oc_polarity;  
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = motor_1_pwm_cpnfig;
  TIM_OC1Init(motor_num, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(motor_num, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = motor_2_pwm_cpnfig;
  TIM_OC2Init(motor_num, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(motor_num, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = motor_3_pwm_cpnfig;
  TIM_OC3Init(motor_num, &TIM_OCInitStructure);	
	TIM_OC3PreloadConfig(motor_num, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = motor_4_pwm_cpnfig;
  TIM_OC4Init(motor_num, &TIM_OCInitStructure);	
	TIM_OC4PreloadConfig(motor_num, TIM_OCPreload_Enable);
	
	TIM_Cmd(motor_num, ENABLE);	
}

//--------------------------初始化电机--------------------------------//
void Motor_Init(void)
{
	Motor_GPIO_Config();
	Motor_MODE_Config();
}

//--------------------------更新电机--------------------------------//
void Motor_Pwm_Flash(int16_t MOTO3_PWM,int16_t MOTO4_PWM,int16_t MOTO2_PWM,int16_t MOTO1_PWM)
{		
     if(MOTO1_PWM >= motor_pwm_max)	MOTO1_PWM = motor_pwm_max;
     if(MOTO2_PWM >= motor_pwm_max)	MOTO2_PWM = motor_pwm_max;
     if(MOTO3_PWM >= motor_pwm_max)	MOTO3_PWM = motor_pwm_max;
     if(MOTO4_PWM >= motor_pwm_max)	MOTO4_PWM = motor_pwm_max;
     if(MOTO1_PWM <= 0)	MOTO1_PWM = 0;
     if(MOTO2_PWM <= 0)	MOTO2_PWM = 0;
     if(MOTO3_PWM <= 0)	MOTO3_PWM = 0;
     if(MOTO4_PWM <= 0)	MOTO4_PWM = 0;
    
     motor_num->CCR2 = MOTO1_PWM;
     motor_num->CCR1 = MOTO2_PWM;
     motor_num->CCR4 = MOTO3_PWM;
     motor_num->CCR3 = MOTO4_PWM;      
}
