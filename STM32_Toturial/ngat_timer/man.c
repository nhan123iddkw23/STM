/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 07/06/2023
* Description: Day la file su dung ngat timer de nhay led
*/

#include <stm32f10x.h>
#include <delay.h>


void config();
void LED1();
void Blinkled();
void LED();
void timer_Init();
void TIM2_IRQHandler();

/*
* Function: TIM2_IRQHandler()
* Description: Ham nay la ham ngat. Khi xay ra ngat se vao ham nay
* Input:
*   none
* Output:
*   none
*/
void TIM2_IRQHandler() {
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)) {
		  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0) {
				 Blinkled();
				}
			  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0) {
				 LED();
				}
			 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0) {
				 LED1();
				 }
			 	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			}
	}
				

int main() {
		config();
		timer_Init();
		while(1) {
       GPIO_SetBits(GPIOB,GPIO_Pin_10);
			 GPIO_SetBits(GPIOB,GPIO_Pin_11);
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			GPIO_SetBits(GPIOB,GPIO_Pin_9);
     Delay_ms(1000);
		   GPIO_ResetBits(GPIOB,GPIO_Pin_10);
			GPIO_ResetBits(GPIOB,GPIO_Pin_11);
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		   GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		   Delay_ms(1000);
			}
		}

/*
* Function: config
* Description: Ham cau hinh GPIOA, GPIOB
* Input:
*   none
* Output:
*   none
*/		
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef BUTTON;
	BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	BUTTON.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	BUTTON.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&BUTTON);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&LED);
	}

/*
* Function: timer_Init
* Description: Ham cau hinh timer 2
* Input:
*   none
* Output:
*   none
*/
	void timer_Init(){
	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef ngat;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	timer.TIM_CounterMode = TIM_CounterMode_Up;  // cau hinh dem len 
	timer.TIM_Period = 200-1;   
	timer.TIM_Prescaler = 3600-1;  // he so chia 3600
	timer.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&timer);    
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);        // cho phep timer 2 hoat dong
	ngat.NVIC_IRQChannel =TIM2_IRQn;
	ngat.NVIC_IRQChannelPreemptionPriority = 0x00;
	ngat.NVIC_IRQChannelSubPriority = 0x00;
	ngat.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&ngat);
}

/*
* Function: Blinkled
* Description: Ham nhay tung led 1
* Input:
*   none
* Output:
*   none
*/		
void Blinkled() {
	 for(uint8_t i = 0; i < 2; i++) {
		 GPIO_SetBits(GPIOB,GPIO_Pin_10);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_11);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_11);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_7);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_8);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_9);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		 Delay_ms(500);
		 }
	 }

	 /*
* Function: LED
* Description: Ham nhay 1 lan 2 led
* Input:
*   none
* Output:
*   none
*/	
void LED() {
	for(uint8_t i = 0; i < 3; i++) {
		 GPIO_SetBits(GPIOB,GPIO_Pin_10);
		 GPIO_SetBits(GPIOB,GPIO_Pin_9);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_11);
		 GPIO_SetBits(GPIOB,GPIO_Pin_8);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_11);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 GPIO_SetBits(GPIOB,GPIO_Pin_7);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		 Delay_ms(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);
		 Delay_ms(500);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		 Delay_ms(500);
		 }
}

/*
* Function: config
* Description: Ham nhay 1 lan 3led
* Input:
*   none
* Output:
*   none
*/	
void LED1(){
	for(uint8_t i = 0; i < 3; i++) {
		 GPIO_SetBits(GPIOB,GPIO_Pin_10);
		 GPIO_SetBits(GPIOB,GPIO_Pin_7);
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 GPIO_SetBits(GPIOB,GPIO_Pin_9);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_11);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		 Delay_ms(1000);
		 GPIO_SetBits(GPIOB,GPIO_Pin_11);
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);
		 GPIO_SetBits(GPIOB,GPIO_Pin_8);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		 Delay_ms(1000);
		 }
}

	
