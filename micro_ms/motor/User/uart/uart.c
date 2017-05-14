#include "uart.h"

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
	NVIC_InitStructure.NVIC_IRQChannel = uart_nvic_irqchannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void UART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	uart_gpio_rcc_cmd(uart_tx_clk|uart_rx_clk, ENABLE);
	uart_af_rcc_cmd(uart_af_clk, ENABLE);
	
	GPIO_PinAFConfig(uart_tx_prot, uart_tx_pinsource, uart_tx_af_usart);
	GPIO_PinAFConfig(uart_rx_prot, uart_rx_pinsource, uart_rx_af_usart);
	
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_InitStruct.GPIO_Pin=uart_tx_pin ;
	GPIO_Init(uart_tx_prot,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=uart_rx_pin;
	GPIO_Init(uart_rx_prot,&GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate=uart_baudrate;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(uart_num ,&USART_InitStruct);
	
	NVIC_Configuration();
	USART_ITConfig(uart_num,USART_IT_RXNE,ENABLE);
	USART_Cmd(uart_num,ENABLE);
}

void UART_SendByte(USART_TypeDef* USARTx,u8 ch)
{
	USART_SendData(USARTx, ch);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}


void UART_SendString(USART_TypeDef* USARTx,char *str)
{
	do
  {
		UART_SendByte(USARTx, *str);
		str++;
	}while(*str !='\0');
	
	while(USART_GetFlagStatus( USARTx,USART_FLAG_TC)==RESET);
}

int fputc(int ch, FILE *f)
{
	USART_SendData(uart_num, (uint8_t)ch);
	while(USART_GetFlagStatus(uart_num, USART_FLAG_TXE) == RESET);		
	
	return (ch);
}

int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(uart_num, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(uart_num);
}






