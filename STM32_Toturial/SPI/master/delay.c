#include <delay.h>

void Init_TIMER() {
		TIM_TimeBaseInitTypeDef DELAY;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		DELAY.TIM_CounterMode = TIM_CounterMode_Up;
		DELAY.TIM_Prescaler = 1;
		DELAY.TIM_Period = 65535;
		TIM_TimeBaseInit(TIM2,&DELAY);
		}
	
		void Delay_1ms() {
			Init_TIMER();
			TIM_Cmd(TIM2,ENABLE);
			TIM_SetCounter(TIM2,0);
			while(TIM_GetCounter(TIM2)<36000);
			TIM_Cmd(TIM2,DISABLE);
			}
		void Delay_ms(unsigned int time_ms) {
			while(time_ms--){
				Delay_1ms();
				}
			}