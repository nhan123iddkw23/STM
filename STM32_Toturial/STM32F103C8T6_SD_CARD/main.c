#include "stm32f10x.h"
#include "delay.h"
#include "ff.h"
#include "spi.h"
FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

void My_GPIO_Init(void);
void My_Uart_Init(void);
void Send_1_byte(char data);
void Send_String(char *str);
int main() {
	UINT bw;
	FRESULT fr;
	
	Delay_Init();
	My_GPIO_Init();
  My_Uart_Init();
	My_SPI_Init();
	f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */

	fr = f_open(&Fil, "Hello.txt", FA_WRITE | FA_CREATE_ALWAYS);	/* Create a file */
	if (fr == FR_OK) {
		Send_String("Truy cap the nho thanh cong");
		f_write(&Fil, "Hello World", 11, &bw);	/* Write data to the file */
		fr = f_close(&Fil);							/* Close the file */
		if (fr == FR_OK && bw == 11) {		/* Lights green LED if data written well */
			while (1) {
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
				Delay_Ms(100);
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
				Delay_Ms(100);
			}
		}
	}
	else if(fr == FR_DISK_ERR){
		
		Send_String("FR_DISK_ERR!!!");
	}
	else if(fr == FR_INT_ERR){
		
		Send_String("FR_INT_ERR!!!");
	}
	else if(fr == FR_NOT_READY){
		
		Send_String("FR_NOT_READY!!!");
	}
	else if(fr == FR_NO_FILE){
		
		Send_String("FR_NO_FILE!!!");
	}
	else if(fr == FR_NO_PATH){
		
		Send_String("FR_NO_PATH!!!");
	}
	else if(fr == FR_INVALID_NAME){
		
		Send_String("FR_INVALID_NAME!!!");
	}
	else if(fr == FR_DENIED){
		
		Send_String("FR_DENIED!!!");
	}
	else if(fr == FR_EXIST){
		
		Send_String("FR_EXIST!!!");
	}
	else if(fr == FR_INVALID_OBJECT){
		
		Send_String("FR_INVALID_OBJECT!!!");
	}
	else if(fr == FR_WRITE_PROTECTED){
		
		Send_String("FR_WRITE_PROTECTED!!!");
	}
	else if(fr == FR_INVALID_DRIVE){
		
		Send_String("FR_INVALID_DRIVE!!!");
	}
  else if(fr == FR_NOT_ENABLED){
		
		Send_String("FR_NOT_ENABLED!!!");
	}
  else if(fr == FR_NO_FILESYSTEM){
		
		Send_String("FR_NO_FILESYSTEM!!!");
	}
  else if(fr == FR_MKFS_ABORTED){
		
		Send_String("FR_MKFS_ABORTED!!!");
	}
  else if(fr == FR_TIMEOUT){
		
		Send_String("FR_TIMEOUT!!!");
	}
  else if(fr == FR_LOCKED){
		
		Send_String("FR_LOCKED!!!");
	}
  else if(fr == FR_NOT_ENOUGH_CORE){
		
		Send_String("FR_NOT_ENOUGH_CORE!!!");
	}
 else if(fr == FR_TOO_MANY_OPEN_FILES){
		
		Send_String("FR_TOO_MANY_OPEN_FILES!!!");
	}
  else if(fr == FR_INVALID_PARAMETER){
		
		Send_String("FR_INVALID_PARAMETER!!!");
	}
	
	while(1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//		  GPIO_ResetBits(GPIOB, GPIO_Pin_12);
//			SPI_I2S_SendData(SPI2, 19);
//	    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET) {
//	    }
//		 GPIO_SetBits(GPIOB, GPIO_Pin_12);
		Delay_Ms(500);
	}
}

void My_GPIO_Init(void) {
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA, &gpioInit);
	
	gpioInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpioInit);
	
}


void My_Uart_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_InitTypeDef uart;
	uart.USART_BaudRate = 115200;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Tx;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_WordLength  = USART_WordLength_8b;
	
	USART_Init(USART1,&uart);
	USART_Cmd(USART1,ENABLE);
	
	}

void Send_1_byte(char data){
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void Send_String(char *str){
	while(*str){
		Send_1_byte(*str);
		str++;
	}
}