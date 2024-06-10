/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 6/06/2023
* Description: Day la file nhay led
*/
#include <stm32f10x.h>
#include <delay.h>
void config();

int main() {
				config();
				Init_TIMER();
				while(1) {
					GPIO_SetBits(GPIOA,GPIO_Pin_0);
					GPIO_SetBits(GPIOB,GPIO_Pin_14);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					GPIO_ResetBits(GPIOB,GPIO_Pin_14);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
					GPIO_SetBits(GPIOB,GPIO_Pin_15);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);
					GPIO_ResetBits(GPIOB,GPIO_Pin_15);
					Delay_ms(500);
					GPIO_SetBits(GPIOA,GPIO_Pin_2);
					GPIO_SetBits(GPIOB,GPIO_Pin_5);
					Delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_2);
					GPIO_ResetBits(GPIOB,GPIO_Pin_5);
					Delay_ms(500);
					}
}

/*
* Function: config
* Description: Ham cau hinh GPIOB | GPIOA
* Input:
*   none
* Output:
*   none
*/
void config() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_All;
	LED.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&LED);
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef LED1;
	LED1.GPIO_Mode = GPIO_Mode_Out_PP;
	LED1.GPIO_Pin = GPIO_Pin_All;
	LED1.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&LED1);
	}
