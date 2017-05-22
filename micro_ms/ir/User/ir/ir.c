#include "ir.h"



__IO uint16_t ADC_ConvertedValue;

static void Rheostat_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT, &GPIO_InitStructure);			
}

static void Rheostat_ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_APB2PeriphClockCmd(RHEOSTAT_ADC_CLK , ENABLE);
	
  RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_DMA_CLK, ENABLE); 
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&ADC_ConvertedValue;  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	DMA_InitStructure.DMA_BufferSize = 1;	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC_DMA_CHANNEL; 
	DMA_Init(RHEOSTAT_ADC_DMA_STREAM, &DMA_InitStructure);
  DMA_Cmd(RHEOSTAT_ADC_DMA_STREAM, ENABLE);

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

  ADC_InitStructure.ADC_NbrOfConversion = 1;                                    
  ADC_Init(RHEOSTAT_ADC, &ADC_InitStructure);
  //---------------------------------------------------------------------------
	
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL, 1, ADC_SampleTime_3Cycles); 
	
  ADC_DMARequestAfterLastTransferCmd(RHEOSTAT_ADC, ENABLE);
  ADC_DMACmd(RHEOSTAT_ADC, ENABLE);
  ADC_Cmd(RHEOSTAT_ADC, ENABLE);  
  ADC_SoftwareStartConv(RHEOSTAT_ADC);
}

void Rheostat_Init(void)
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
}
