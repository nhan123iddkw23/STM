/*
* File: delay.c
* Author: Hoang Minh Nhan
* Date: 6/06/2023
* Description: Day la file tao delay
*/
#include <delay.h>

/*
* Function: Init_Timer
* Description: Ham cau hinh Timer2
* Input:
*   none
* Output:
*   none
*/
void Init_TIMER() {
		TIM_TimeBaseInitTypeDef DELAY;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		DELAY.TIM_CounterMode = TIM_CounterMode_Up;
		DELAY.TIM_Prescaler = 2-1; // he so chia = 2
		DELAY.TIM_Period = 65535;
		TIM_TimeBaseInit(TIM2,&DELAY);
		}

/*
* Function: Delay_1ms
* Description: Ham tao do tre 1ms
* Input:
*   none
* Output:
*   none
*/		
void Delay_1ms() {
			Init_TIMER(); // ham cau hinh timer
			TIM_Cmd(TIM2,ENABLE);           // cho phep TIM2 hoat dong
			TIM_SetCounter(TIM2,0);        // dat gia tri ban dau cho TIM2
			while(TIM_GetCounter(TIM2)<36000); //Lap den khi gia tri bo dem nho hon 36000
			TIM_Cmd(TIM2,DISABLE); // khong cho phep timer hoat dong
			}

/*
* Function: Delay_ms
* Description: Ham tao do tre 
* Input:
*   time_ms kieu unsigned int
* Output:
*   none
*/
void Delay_ms(unsigned int time_ms) {
			while(time_ms--){
				Delay_1ms();
				}
			}