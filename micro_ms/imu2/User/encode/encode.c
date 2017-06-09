#include "encode.h"

int32_t encode_1_velocity=0, encode_2_velocity=0;
int32_t encode_1_pulse_total=0, encode_2_pulse_total=0;
int32_t encode_1_pulse_new=0, encode_2_pulse_new=0;
int32_t encode_1_pulse_old=0, encode_2_pulse_old=0;


static void Encode_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	encode_gpio_rcc_cmd(encode_1a_clk|encode_1b_clk|encode_2a_clk|encode_2b_clk, ENABLE); 
	
	GPIO_PinAFConfig(encode_1a_port, encode_1a_pinsource, encode_1a_af); 
	GPIO_PinAFConfig(encode_1b_port, encode_1b_pinsource, encode_1b_af);
	GPIO_PinAFConfig(encode_2a_port, encode_2a_pinsource, encode_2a_af);
	GPIO_PinAFConfig(encode_2b_port, encode_2b_pinsource, encode_2b_af);
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = encode_1a_pin;
	GPIO_Init(encode_1a_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = encode_1b_pin;
	GPIO_Init(encode_1b_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = encode_2a_pin;
	GPIO_Init(encode_2a_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = encode_2b_pin;
	GPIO_Init(encode_2b_port, &GPIO_InitStructure);
}

static void Encode_Mode_Init(void)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	encode_clk_rcc_cmd(encode_1_clk|encode_2_clk, ENABLE);
	
	TIM_DeInit(encode_1_num);
	TIM_DeInit(encode_2_num);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = encode_period - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = encode_prescaler;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(encode_1_num, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(encode_2_num, &TIM_TimeBaseInitStruct);

  TIM_EncoderInterfaceConfig(encode_1_num, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_EncoderInterfaceConfig(encode_2_num, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter = encode_filter;
	TIM_ICInit(encode_1_num, &TIM_ICInitStruct); 
	TIM_ICInit(encode_2_num, &TIM_ICInitStruct);
	
	TIM_ClearFlag(encode_1_num, TIM_FLAG_Update);
	TIM_ClearFlag(encode_2_num, TIM_FLAG_Update);
	TIM_SetCounter(encode_1_num, 0);
	TIM_SetCounter(encode_2_num, 0);
	
	TIM_Cmd(encode_1_num, ENABLE);
	TIM_Cmd(encode_2_num, ENABLE);
}

void Encode_Init(void)
{
	Encode_GPIO_Init();
	Encode_Mode_Init();
}
void Encode_Velocity_Get(void)
{
	encode_1_pulse_new = (int32_t)TIM_GetCounter(encode_1_num);
	encode_1_velocity = encode_1_pulse_new - encode_1_pulse_old;
	encode_1_pulse_old = encode_1_pulse_new;
	if(encode_1_velocity > 32767)
		encode_1_velocity -= 65536;
	else if(encode_1_velocity < -32767)
		encode_1_velocity += 65536;
	encode_1_pulse_total += encode_1_velocity;
	
	encode_2_pulse_new = (int32_t)TIM_GetCounter(encode_2_num);
	encode_2_velocity = encode_2_pulse_new - encode_2_pulse_old;
	encode_2_pulse_old = encode_2_pulse_new;
	if(encode_2_velocity > 32767)
		encode_2_velocity -= 65536;
	else if(encode_2_velocity < -32767)
		encode_2_velocity += 65536;
	encode_2_pulse_total += encode_2_velocity;
}

void Ready_Start(void)
{
	while(encode_1_pulse_total/4 < 500);
	led_s1_on;
	while(encode_2_pulse_total/4 < 500);
	led_s2_on;
}

