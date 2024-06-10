#include "stm32f10x.h"

void UART_Config(void);
void GPIO_Config(void);
void UART_SendChar(char data);
void Delay_1_Ms(void);
void Delay_Ms(uint32_t u32Delay);
void UART_Send_String(char *str);
void Delay_1_Ms(void)
{
	
	SysTick->LOAD = 72 * 1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	while (!(SysTick->CTRL & (1 << 16))) {
	}
}

void Delay_Ms(uint32_t u32Delay)
{
	
	while (u32Delay) {
		Delay_1_Ms();
		--u32Delay;
	}
}

int main(){
	GPIO_Config();
	UART_Config();
 while(1){
	UART_Send_String("Minh Nhan \r\n");
  Delay_Ms(1000); 
 }
}


void GPIO_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin  = GPIO_Pin_9;
	gpio.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpio);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef Led;
	Led.GPIO_Mode = GPIO_Mode_Out_PP;
	Led.GPIO_Pin  = GPIO_Pin_13;
	Led.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&Led);
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
	while(*str) {
	    UART_SendChar(*str);
		  str++;
		}
}





