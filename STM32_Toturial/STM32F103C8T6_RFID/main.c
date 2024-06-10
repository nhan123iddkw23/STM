#include "stm32f10x.h"
#include "delay.h"
#include "mfrc522.h"
#include <stdio.h>

void My_GPIO_Init(void);
void UART_Config(void);
void UART_SendChar(char data);
uint8_t CardID[5];
char szBuff[100];
void UART_Send_String(char *str);
int main() {
	Delay_Init();
	My_GPIO_Init();
	TM_MFRC522_Init();
	UART_Config();
	UART_Send_String("Lon");
	UART_SendChar('B');
	while(1) {
		if(TM_MFRC522_Check(CardID) == MI_OK) {
			UART_Send_String("Bu");
			sprintf(szBuff, "ID: 0x%02X%02X%02X%02X%02X", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
      UART_Send_String(szBuff); 
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
		}
	  else if(TM_MFRC522_Check(CardID) == MI_NOTAGERR)
	   {
      UART_Send_String("MI_NOTAGERR"); 
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
		}
	
	 else if(TM_MFRC522_Check(CardID) == MI_ERR)
	    {
      UART_Send_String("MI_ERR\n"); 
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(500);
		}
	}
}

void My_GPIO_Init(void) {
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin  = GPIO_Pin_9;
	gpioInit.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpioInit);
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioInit);
}


void UART_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_InitTypeDef USART_Initstruct;
	USART_Initstruct.USART_BaudRate = 115200;
	USART_Initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstruct.USART_Mode                = USART_Mode_Tx |USART_Mode_Rx;
	USART_Initstruct.USART_Parity              = USART_Parity_No;
	USART_Initstruct.USART_StopBits            = USART_StopBits_1;
	USART_Initstruct.USART_WordLength          = USART_WordLength_8b;
	USART_Init(USART1,&USART_Initstruct);
	USART_Cmd(USART1,ENABLE);
} 

void UART_SendChar(char data){
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void UART_Send_String(char *str){
	  while(*str){
			UART_SendChar(*str);
			str++;
		}
}
