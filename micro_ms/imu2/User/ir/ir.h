#ifndef __IR_H_
#define __IR_H_
#include "stm32f4xx.h"
#include "stdio.h"



#define ir_adc_config_times								1000
#define ir_adc_1_buffer										150
#define ir_adc_2_buffer										150
#define ir_adc_1_conversion     					3
#define ir_adc_2_conversion     					3
#define ir_adc_1_conversion_times     		50
#define ir_adc_2_conversion_times     		50


#define ir_adc_gpio_rcc_cmd               RCC_AHB1PeriphClockCmd
#define ir_adc_clk_rcc_cmd							  RCC_APB2PeriphClockCmd
#define ir_adc_dma_rcc_cmd							  RCC_AHB1PeriphClockCmd
#define ir_adc_1_clk         			        RCC_APB2Periph_ADC1
#define ir_adc_2_clk         			        RCC_APB2Periph_ADC2
#define ir_adc_1_num											ADC1
#define ir_adc_2_num											ADC2

#define ir_adc_1a_port    								GPIOC
#define ir_adc_1a_pin    									GPIO_Pin_5
#define ir_adc_1a_gpio_clk    				    RCC_AHB1Periph_GPIOC
#define ir_adc_1a_channel								  ADC_Channel_15

#define ir_adc_1b_port    								GPIOC
#define ir_adc_1b_pin    									GPIO_Pin_4
#define ir_adc_1b_gpio_clk    				    RCC_AHB1Periph_GPIOC
#define ir_adc_1b_channel								  ADC_Channel_14

#define ir_adc_1c_port    								GPIOA
#define ir_adc_1c_pin    									GPIO_Pin_7
#define ir_adc_1c_gpio_clk    				    RCC_AHB1Periph_GPIOA
#define ir_adc_1c_channel								  ADC_Channel_7

#define ir_adc_2a_port    								GPIOA
#define ir_adc_2a_pin    									GPIO_Pin_4
#define ir_adc_2a_gpio_clk    				    RCC_AHB1Periph_GPIOA
#define ir_adc_2a_channel								  ADC_Channel_4

#define ir_adc_2b_port    								GPIOA
#define ir_adc_2b_pin    									GPIO_Pin_5
#define ir_adc_2b_gpio_clk    				    RCC_AHB1Periph_GPIOA
#define ir_adc_2b_channel								  ADC_Channel_5

#define ir_adc_2C_port    								GPIOA
#define ir_adc_2C_pin    									GPIO_Pin_6
#define ir_adc_2C_gpio_clk    				    RCC_AHB1Periph_GPIOA
#define ir_adc_2C_channel								  ADC_Channel_6

#define ir_adc_1_dma_clk							    RCC_AHB1Periph_DMA2
#define ir_adc_1_dma_channel							DMA_Channel_0
#define ir_adc_1_dma_strean								DMA2_Stream0

#define ir_adc_2_dma_clk							    RCC_AHB1Periph_DMA2
#define ir_adc_2_dma_channel							DMA_Channel_1
#define ir_adc_2_dma_strean								DMA2_Stream2

#define ir_adc_1_addr      				        ((u32)ir_adc_1_num+0x4C)
#define ir_adc_2_addr                     ((u32)ir_adc_2_num+0x4C)


#define ir_out_gpio_rcc_cmd								RCC_AHB1PeriphClockCmd
#define ir_out_clk_rcc_cmd							  RCC_APB2PeriphClockCmd
#define ir_out_clk							     			RCC_APB2Periph_TIM1
#define ir_out_num												TIM1

#define ir_out_1_port       							GPIOE  
#define ir_out_1_pin             					GPIO_Pin_9                  
#define ir_out_1_pinsource							  GPIO_PinSource9
#define ir_out_1_gpio_clk									RCC_AHB1Periph_GPIOE
#define ir_out_1_af								   			GPIO_AF_TIM1 
#define ir_out_1_ccr											CCR1		
#define ir_1_on    										    ir_out_1_port->BSRRL = ir_out_1_pin
#define ir_1_off  			   							  ir_out_1_port->BSRRH = ir_out_1_pin

#define ir_out_2_port       							GPIOE  
#define ir_out_2_pin             				  GPIO_Pin_11                  
#define ir_out_2_pinsource								GPIO_PinSource11
#define ir_out_2_gpio_clk									RCC_AHB1Periph_GPIOE
#define ir_out_2_af								   			GPIO_AF_TIM1 
#define ir_out_2_ccr											CCR2	
#define ir_2_on    										    ir_out_2_port->BSRRL = ir_out_2_pin
#define ir_2_off  			   							  ir_out_2_port->BSRRH = ir_out_2_pin

#define ir_out_3_port       							GPIOE  
#define ir_out_3_pin             					GPIO_Pin_13                  
#define ir_out_3_pinsource								GPIO_PinSource13
#define ir_out_3_gpio_clk									RCC_AHB1Periph_GPIOE
#define ir_out_3_af								   			GPIO_AF_TIM1 
#define ir_out_3_ccr											CCR3	
#define ir_3_on    										    ir_out_3_port->BSRRL = ir_out_3_pin
#define ir_3_off  			   							  ir_out_3_port->BSRRH = ir_out_3_pin

#define IR_Out_1_OC_Init(a,b)  						TIM_OC1Init(a,b);	
#define IR_Out_1_OC_Preload_Config(a,b) 	TIM_OC1PreloadConfig(a,b);

#define IR_Out_2_OC_Init(a,b)  						TIM_OC2Init(a,b);	
#define IR_Out_2_OC_Preload_Config(a,b) 	TIM_OC2PreloadConfig(a,b);

#define IR_Out_3_OC_Init(a,b)  						TIM_OC3Init(a,b);	
#define IR_Out_3_OC_Preload_Config(a,b) 	TIM_OC3PreloadConfig(a,b);

#define ir_out_pwm												90

#define ir_start_value										4000
#define ir_start_value_back								200   //250

extern __IO u32 ir_adc_1a_value, ir_adc_1b_value, ir_adc_1c_value;
extern __IO u32 ir_adc_2a_value, ir_adc_2b_value, ir_adc_2c_value;
extern __IO u32 ir_adc_1a_value_sum, ir_adc_1b_value_sum, ir_adc_1c_value_sum;
extern __IO u32 ir_adc_2a_value_sum, ir_adc_2b_value_sum, ir_adc_2c_value_sum;
extern __IO u16 ir_adc_1a_value_new, ir_adc_1b_value_new, ir_adc_1c_value_new;
extern __IO u16 ir_adc_2a_value_new, ir_adc_2b_value_new, ir_adc_2c_value_new;
extern __IO u16 ir_adc_1_get[ir_adc_1_buffer];
extern __IO u16 ir_adc_2_get[ir_adc_2_buffer];


static void IR_ADC_GPIO_Config(void);
static void IR_ADC_Mode_Config(void);
void IR_ADC_Init(void);
void IR_ADC_GetData(void);
void IR_ADC_ADV(void);
void IR_ADC_Dataup(void);
void IR_Out_GPIO_Config(void);
void IR_OUT_Mode(void);


#endif

