/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 10/06/2023
* Description: Day la file code nhay 4 led multitask
*/
#include <stm32f10x.h>
#include <delay.h>

typedef struct{
	void (*func)();
	uint32_t time;
	uint32_t delay;
}task;

static uint32_t count = 0;
uint32_t mallis();
void config_GPIOA();
void multitask(task *tasks);
void config_TIM2();
void led1();
void led2();
void led3();
void led4();

/*
* Function: TIM2_IRQHandler
* Description: Ham ccon phuc vu ngat
* Input:
*   none
* Output:
*   none
*/
void TIM2_IRQHandler() { 
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)) {  // doc co ngat 
			count++; // tang bien count
			}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); // xoa co ngat
}

/*
* Function: mallis
* Description: ham tra ve bien count
* Input:
*   none
* Output:
*   return count
*/
uint32_t mallis(){
	return count;
}


	int main() {
		config_GPIOA();
		config_TIM2();
		task task1 ={&led1,mallis(),1000}; // mallis - time = 1000;
		task task2 ={&led2,mallis(),2000}; 
		task task3 ={&led3,mallis(),3000};
		task task4 ={&led4,mallis(),5000};
		while(1) {
			multitask(&task1);
			multitask(&task2);
			multitask(&task3);
			multitask(&task4);
		}
}
	


/*
* Function: config_GPIOA
* Description: Ham cau hinh GPIOA
* Input:
*   none
* Output:
*   none
*/
void config_GPIOA(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&LED);
	}

/*
* Function: config_TIM2
* Description: Ham cau hinh TIM2
* Input:
*   none
* Output:
*   none
*/
void config_TIM2(){
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	 TIM_TimeBaseInitTypeDef Timer;
	 Timer.TIM_ClockDivision = TIM_CKD_DIV1;
	 Timer.TIM_Period = 20-1;
	 Timer.TIM_Prescaler = 3600-1; // he so chia 3600
	 Timer.TIM_CounterMode = TIM_CounterMode_Up; // dem len
	 TIM_TimeBaseInit(TIM2,&Timer);
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	 TIM_Cmd(TIM2,ENABLE); // bat timer
	 NVIC_InitTypeDef interrupt;
	 interrupt.NVIC_IRQChannel = TIM2_IRQn; // chon TIM2 la ngat
	 interrupt.NVIC_IRQChannelCmd = ENABLE; // bat ngat ngoai
	 interrupt.NVIC_IRQChannelPreemptionPriority = 0;
	 interrupt.NVIC_IRQChannelSubPriority = 0;
	 NVIC_Init(&interrupt);
	}
	
/*
* Function: multitask
* Description: Ham tao khoang delay va goi ham
* Input:
*   tasks  - Day la bien kieu enum
* Output:
*   none
*/	
void multitask(task *tasks) {
	if(mallis() - tasks->time >= tasks->delay) { 
		tasks->func(); // goi 1 trong 4 ham led
		tasks->time = mallis(); 
		}
}
	
/*
* Function: led1
* Description: Ham dao trang thai led
* Input:
*   none
* Output:
*   none
*/	
void led1(){
     GPIOA->ODR ^= GPIO_Pin_0;   // dao trang thai tren chan PA0
	 }
/*
* Function: led2
* Description: Ham dao trang thai led
* Input:
*   none
* Output:
*   none
*/	
void led2(){
     GPIOA->ODR ^= GPIO_Pin_1;    // dao trang thai tren chan PA1
	 }
/*
* Function: led3
* Description: Ham dao trang thai led
* Input:
*   none
* Output:
*   none
*/	
void led3(){
     GPIOA->ODR ^= GPIO_Pin_2;    // dao trang thai tren chan PA2
	 }
/*
* Function: led4
* Description: Ham dao trang thai led
* Input:
*   none
* Output:
*   none
*/	
void led4(){
     GPIOA->ODR ^= GPIO_Pin_3;    // dao trang thai tren chan PA3
	 }
 