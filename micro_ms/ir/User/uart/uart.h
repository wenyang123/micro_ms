#ifndef __UART_H_
#define __UART_H_
#include "stm32f4xx.h"
#include "stdio.h"

#define uart_gpio_rcc_cmd        RCC_AHB1PeriphClockCmd 
#define uart_af_rcc_cmd          RCC_APB2PeriphClockCmd
#define uart_af_clk              RCC_APB2Periph_USART1
#define uart_baudrate            115200
#define uart_num                 USART1
#define uart_nvic_irqchannel     USART1_IRQn

#define uart_tx_clk      				 RCC_AHB1Periph_GPIOA
#define uart_tx_pin              GPIO_Pin_9
#define uart_tx_prot             GPIOA
#define uart_tx_pinsource        GPIO_PinSource9
#define uart_tx_af_usart         GPIO_AF_USART1

#define uart_rx_clk              RCC_AHB1Periph_GPIOA
#define uart_rx_pin              GPIO_Pin_10
#define uart_rx_prot             GPIOA
#define uart_rx_pinsource        GPIO_PinSource10
#define uart_rx_af_usart         GPIO_AF_USART1
 
static void NVIC_Configuration(void);
void UART_Config(void);
void UART_SendByte(USART_TypeDef* USARTx,u8 ch);
void UART_SendString(USART_TypeDef* USARTx,char *str);
	
#endif
