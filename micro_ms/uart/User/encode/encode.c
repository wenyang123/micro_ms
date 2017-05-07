#include "encode.h"

static void Encode_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	encode_gpio_rcc_cmd(encode_1a_clk|encode_1b_clk|encode_2a_clk|encode_2b_clk, ENABLE); 
  encode_clk_rcc_cmd(encode_1_clk|encode_2_clk, ENABLE);
	
	GPIO_PinAFConfig(encode_1a_port, encode_1a_pinsource, encode_1a_af); 
	GPIO_PinAFConfig(encode_1b_port, encode_1b_pinsource, encode_1b_af);
	GPIO_PinAFConfig(encode_2a_port, encode_2a_pinsource, encode_2a_af);
	GPIO_PinAFConfig(encode_2b_port, encode_2b_pinsource, encode_2b_af);
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
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

void Encode_Init(void)
{
	Encode_GPIO_Init();
}
