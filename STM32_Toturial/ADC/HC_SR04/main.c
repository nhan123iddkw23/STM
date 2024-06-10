#include "stm32f10x.h"

/*#define TRIG GPIO_Pin_11
#define ECHO GPIO_Pin_10
uint16_t data;
uint16_t time1;
float khoang_cach = 0;


void GPIO_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	// Cau hinh chan TRIG //
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = TRIG;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&gpio);
	// Cau hinh chan ECHO //
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = ECHO;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&gpio);
	
}

//void TIMER_Config() {
void Init_TIMER() {
		TIM_TimeBaseInitTypeDef DELAY;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		DELAY.TIM_CounterMode = TIM_CounterMode_Up;
		DELAY.TIM_Prescaler = 2-1; // he so chia = 2
		DELAY.TIM_Period = 65535;
		TIM_TimeBaseInit(TIM2,&DELAY);
		}

	
void Delay_1us() {
			Init_TIMER(); // ham cau hinh timer
			TIM_Cmd(TIM2,ENABLE);           // cho phep TIM2 hoat dong
			TIM_SetCounter(TIM2,0);        // dat gia tri ban dau cho TIM2
			while(TIM_GetCounter(TIM2)<36); //Lap den khi gia tri bo dem nho hon 36
			TIM_Cmd(TIM2,DISABLE); // khong cho phep timer hoat dong
			}

			
void Delay_1ms() {
			Init_TIMER(); // ham cau hinh timer
			TIM_Cmd(TIM2,ENABLE);           // cho phep TIM2 hoat dong
			TIM_SetCounter(TIM2,0);        // dat gia tri ban dau cho TIM2
			while(TIM_GetCounter(TIM2)<36000); //Lap den khi gia tri bo dem nho hon 36
			TIM_Cmd(TIM2,DISABLE); // khong cho phep timer hoat dong
			}

void Delay_us(unsigned int time_us) {
			while(time_us--){
				Delay_1us();
				}
			}

void Delay_ms(unsigned int time_ms) {
			while(time_ms--){
				Delay_1ms();
				}
			}


void Send_data_trig() {
	 GPIO_ResetBits(GPIOB,TRIG);
	 Delay_us(10);
	 GPIO_SetBits(GPIOB,TRIG);
	 Delay_us(15);
	 GPIO_ResetBits(GPIOB,TRIG);
	 Delay_us(10);
}

void Receive_data_echo() {
//	TIMER_Config();
	// cho chan echo len muc 1 //
	while(GPIO_ReadInputDataBit(GPIOB,ECHO) == 0) ;
	TIM_SetCounter(TIM2,0);
	// cho chan echo xuong muc 0 //
	while(GPIO_ReadInputDataBit(GPIOB,ECHO) == 1);
	data = TIM_GetCounter(TIM2);
}
	
	
int main() {
	 GPIO_Config();
	// TIMER_Config();
	 Init_TIMER();
	while(1) {
	//	GPIO_SetBits(GPIOB,TRIG);
	//	Delay_us(500);
	//	GPIO_ResetBits(GPIOB,TRIG);
	//	Delay_us(500);
	 Send_data_trig();
	 Receive_data_echo();
	 time1 = (data*8);
	 khoang_cach = (time1*34000)/2.0;
		Delay_ms(500);
	}
} */

#include <HC_SR04.h>
#include <stm32f10x.h>
#include <delay.h>
#include <lcd.h>
#include <stdio.h>


void EnableHCSR04PeriphClock() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

int16_t dist = 0;

int main(void) {
	InitHCSR04();
	LCD_Init();
	while (1){
		dist = HCSR04GetDistance();
		LCD_Gotoxy(0,0);
		LCD_Number(dist);
		Delay_ms(200);
		LCD_Send_Command(0x01); 
	}
} 