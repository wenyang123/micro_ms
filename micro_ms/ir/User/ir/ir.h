#ifndef __ADC_H
#define	__ADC_H


#include "stm32f4xx.h"
#define RHEOSTAT_PC3     1

#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC1+0x4c)

#define RHEOSTAT_ADC_GPIO_PORT    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN     GPIO_Pin_4
#define RHEOSTAT_ADC_GPIO_CLK     RCC_AHB1Periph_GPIOC

#define RHEOSTAT_ADC              ADC1
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC1
#define RHEOSTAT_ADC_CHANNEL      ADC_Channel_14

#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_0
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0

void Rheostat_Init(void);


#endif 

