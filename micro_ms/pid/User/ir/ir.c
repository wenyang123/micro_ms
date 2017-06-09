#include "ir.h"

__IO u16 ir_adc_1_get[ir_adc_1_buffer]={0};
__IO u16 ir_adc_2_get[ir_adc_2_buffer]={0};
__IO u32 ir_adc_1a_value=0, ir_adc_1b_value=0, ir_adc_1c_value=0;
__IO u32 ir_adc_2a_value=0, ir_adc_2b_value=0, ir_adc_2c_value=0;
__IO u16 ir_adc_1a_value_new=0, ir_adc_1b_value_new=0, ir_adc_1c_value_new=0;
__IO u16 ir_adc_2a_value_new=0, ir_adc_2b_value_new=0, ir_adc_2c_value_new=0;
__IO u32 ir_adc_1a_value_sum=0, ir_adc_1b_value_sum=0, ir_adc_1c_value_sum=0;
__IO u32 ir_adc_2a_value_sum=0, ir_adc_2b_value_sum=0, ir_adc_2c_value_sum=0;

u32 ir_adc_systimes=0;

static void IR_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ir_adc_gpio_rcc_cmd(ir_adc_1a_gpio_clk|ir_adc_1b_gpio_clk|ir_adc_1c_gpio_clk|\
											ir_adc_2a_gpio_clk|ir_adc_2b_gpio_clk|ir_adc_2C_gpio_clk, ENABLE);
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //不上拉不下拉
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_1a_pin;
	GPIO_Init(ir_adc_1a_port, &GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_1b_pin;
	GPIO_Init(ir_adc_1b_port, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_1c_pin;
	GPIO_Init(ir_adc_1c_port, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_2a_pin;
	GPIO_Init(ir_adc_2a_port, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_2b_pin;
	GPIO_Init(ir_adc_2b_port, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = ir_adc_2C_pin;
	GPIO_Init(ir_adc_2C_port, &GPIO_InitStructure);				
}

static void IR_ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	ir_adc_clk_rcc_cmd(ir_adc_1_clk|ir_adc_2_clk, ENABLE);
  ir_adc_dma_rcc_cmd(ir_adc_1_dma_clk|ir_adc_2_dma_clk, ENABLE); 
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ir_adc_1_addr;	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&ir_adc_1_get; 
	DMA_InitStructure.DMA_BufferSize = ir_adc_1_buffer;	
	DMA_InitStructure.DMA_Channel = ir_adc_1_dma_channel; 
	DMA_Init(ir_adc_1_dma_strean, &DMA_InitStructure);
  DMA_Cmd(ir_adc_1_dma_strean, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ir_adc_2_addr;	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&ir_adc_2_get; 
	DMA_InitStructure.DMA_BufferSize = ir_adc_2_buffer;	
	DMA_InitStructure.DMA_Channel = ir_adc_2_dma_channel; 
	DMA_Init(ir_adc_2_dma_strean, &DMA_InitStructure);
  DMA_Cmd(ir_adc_2_dma_strean, ENABLE);

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
  ADC_InitStructure.ADC_NbrOfConversion = ir_adc_1_conversion;                                    
  ADC_Init(ir_adc_1_num, &ADC_InitStructure);
	
	ADC_InitStructure.ADC_NbrOfConversion = ir_adc_2_conversion;                                    
  ADC_Init(ir_adc_2_num, &ADC_InitStructure);
  //---------------------------------------------------------------------------
	
 
  ADC_RegularChannelConfig(ir_adc_1_num,ir_adc_1a_channel,1,ADC_SampleTime_3Cycles); 
  ADC_RegularChannelConfig(ir_adc_1_num,ir_adc_1b_channel,2,ADC_SampleTime_3Cycles); 
  ADC_RegularChannelConfig(ir_adc_1_num,ir_adc_1c_channel,3,ADC_SampleTime_3Cycles); 

	ADC_RegularChannelConfig(ir_adc_2_num,ir_adc_2a_channel,1,ADC_SampleTime_3Cycles); 
  ADC_RegularChannelConfig(ir_adc_2_num,ir_adc_2b_channel,2,ADC_SampleTime_3Cycles); 
  ADC_RegularChannelConfig(ir_adc_2_num,ir_adc_2C_channel,3,ADC_SampleTime_3Cycles); 
	
  ADC_DMARequestAfterLastTransferCmd(ir_adc_1_num, ENABLE);
  ADC_DMACmd(ir_adc_1_num, ENABLE);
  ADC_Cmd(ir_adc_1_num, ENABLE);  
	
	ADC_DMARequestAfterLastTransferCmd(ir_adc_2_num, ENABLE);
  ADC_DMACmd(ir_adc_2_num, ENABLE);
  ADC_Cmd(ir_adc_2_num, ENABLE);  
	
  ADC_SoftwareStartConv(ir_adc_1_num);
  ADC_SoftwareStartConv(ir_adc_2_num);
}

void IR_ADC_Init(void)
{
	IR_ADC_GPIO_Config();
	IR_ADC_Mode_Config();
}

void IR_ADC_GetData(void)
{
	u8 i=0, j=0;
	ir_adc_1a_value = 0; ir_adc_1b_value = 0; ir_adc_1c_value = 0;
	ir_adc_2a_value = 0; ir_adc_2b_value = 0; ir_adc_2c_value = 0;
	
	for(j=0; j<ir_adc_1_conversion_times; j++)
  {
		i = j * ir_adc_1_conversion;
		ir_adc_1a_value = ir_adc_1a_value + ir_adc_1_get[i];
		ir_adc_1b_value = ir_adc_1b_value + ir_adc_1_get[i+1];
		ir_adc_1c_value = ir_adc_1c_value + ir_adc_1_get[i+2];
	}
	for(j=0; j<ir_adc_2_conversion_times; j++)
  {
		i = j * ir_adc_2_conversion;
		ir_adc_2a_value = ir_adc_2a_value + ir_adc_2_get[i];
		ir_adc_2b_value = ir_adc_2b_value + ir_adc_2_get[i+1];
		ir_adc_2c_value = ir_adc_2c_value + ir_adc_2_get[i+2];
	}

	
	ir_adc_1a_value = ir_adc_1a_value/ir_adc_1_conversion_times;
	ir_adc_1b_value = ir_adc_1b_value/ir_adc_1_conversion_times;
	ir_adc_1c_value = ir_adc_1c_value/ir_adc_1_conversion_times;

	ir_adc_2a_value = ir_adc_2a_value/ir_adc_2_conversion_times;
	ir_adc_2b_value = ir_adc_2b_value/ir_adc_2_conversion_times;
	ir_adc_2c_value = ir_adc_2c_value/ir_adc_2_conversion_times;
}
void IR_ADC_ADV(void)
{
	if(ir_adc_systimes > ir_adc_config_times)
	{	
		return;
	}
	
	if(ir_adc_systimes == ir_adc_config_times)
	{
		ir_adc_1a_value_sum = ir_adc_1a_value_sum/ir_adc_config_times;
		ir_adc_1b_value_sum = ir_adc_1b_value_sum/ir_adc_config_times;
		ir_adc_1c_value_sum = ir_adc_1c_value_sum/ir_adc_config_times;
		
		ir_adc_2a_value_sum = ir_adc_2a_value_sum/ir_adc_config_times;
		ir_adc_2b_value_sum = ir_adc_2b_value_sum/ir_adc_config_times;
		ir_adc_2c_value_sum = ir_adc_2c_value_sum/ir_adc_config_times;
		
		ir_adc_systimes++;
		return;
	}
	
	if(ir_adc_systimes == 0)
	{
		ir_adc_1a_value_sum=0; ir_adc_1b_value_sum=0; ir_adc_1c_value_sum=0;
		ir_adc_2a_value_sum=0; ir_adc_2b_value_sum=0; ir_adc_2c_value_sum=0;
	}
	
	ir_adc_1a_value_sum += ir_adc_1a_value;
	ir_adc_1b_value_sum += ir_adc_1b_value;
	ir_adc_1c_value_sum += ir_adc_1c_value;
	ir_adc_2a_value_sum += ir_adc_2a_value;
	ir_adc_2b_value_sum += ir_adc_2b_value;
	ir_adc_2c_value_sum += ir_adc_2c_value;
	
	ir_adc_systimes ++;
}

void IR_Out_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
	ir_out_gpio_rcc_cmd(ir_out_1_gpio_clk|ir_out_2_gpio_clk|ir_out_3_gpio_clk, ENABLE); 
	
//	GPIO_PinAFConfig(ir_out_1_port,ir_out_1_pinsource,ir_out_1_af);
//	GPIO_PinAFConfig(ir_out_2_port,ir_out_2_pinsource,ir_out_2_af);
//	GPIO_PinAFConfig(ir_out_3_port,ir_out_3_pinsource,ir_out_3_af);
	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = ir_out_1_pin;
	GPIO_Init(ir_out_1_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ir_out_2_pin;
	GPIO_Init(ir_out_2_port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ir_out_3_pin;
	GPIO_Init(ir_out_3_port, &GPIO_InitStructure);
	
	ir_1_off;ir_2_off;ir_3_off;
}

void IR_OUT_Mode(void)
{		
  ir_out_num->ir_out_1_ccr = ir_out_pwm;
	ir_out_num->ir_out_2_ccr = ir_out_pwm;
  ir_out_num->ir_out_3_ccr = ir_out_pwm;
}

void IR_ADC_Dataup(void)
{
		IR_ADC_GetData();
		IR_ADC_ADV();
	
	  ir_adc_1a_value_new = ir_adc_1a_value;
		ir_adc_1b_value_new = ir_adc_1b_value;
		ir_adc_1c_value_new = ir_adc_1c_value;
		
		ir_adc_2a_value_new = ir_adc_2a_value;
		ir_adc_2b_value_new = ir_adc_2b_value;
		ir_adc_2c_value_new = ir_adc_2c_value;
}





