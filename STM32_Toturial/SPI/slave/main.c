/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 17/06/2023
* Description: Day la file slave
*/

#include <stm32f10x.h>
#include <delay.h>
#include <stdbool.h>

uint8_t x = 0;
uint8_t data = 0x00;
bool check;

void config();
uint8_t SPI_Recevie();
void program();

/*
* Function: config
* Description: Ham cau hinh GPIOA,GPIOB
* Input:
*   none
* Output:
*   none
*/
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef SPI;
	SPI.GPIO_Mode = GPIO_Mode_IPU;
	SPI.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	SPI.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&SPI);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	LED.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&LED);
}


/*
* Function: SPI_Recevie
* Description: Ham nhan du lieu
* Input:
*   none
* Output:
*  data
*/
uint8_t SPI_Recevie() {
	 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 1); // Cho truyen data
		// Doc chan SS neu ss = 0 thi bat dau nhan du lieu
		 while(x<8) {   
			 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1){ //Doc xung chan CLK
			 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1); // Doc xung chan CLK
				 check = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
			 data = data<<1; // Dich 1 sang trai 1 bit
			 data = data|check; // Toan tu or voi chan nhan du lieu, 
			 x++; // tang bien x
		 }
			 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
	 }
		 return data;
 }

void program() {
	   if(SPI_Recevie() == 56) {
		 GPIO_SetBits(GPIOB,GPIO_Pin_0);
	   Delay_ms(1000);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	   Delay_ms(1000);
	 }
 }
int main() {
	 config();
	   while(1) {
			program();
	 }
 }
 
		 