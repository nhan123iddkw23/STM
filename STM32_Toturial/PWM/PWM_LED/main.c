#include <stm32f10x.h>
#include <delay.h>

void PWM_StandardLibrary(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef timerInit;
	TIM_OCInitTypeDef pwmInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 10000 - 1;
	timerInit.TIM_Prescaler = 7200 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
	
	/* Ch1 with duty 10 % */
//	pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
//	pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
//	pwmInit.TIM_Pulse = (10*10000)/100;
///	pwmInit.TIM_OutputState = TIM_OutputState_Enable;
	//TIM_OC1Init(TIM2, &pwmInit);
	
	/* Ch2 with duty 25 % */
	pwmInit.TIM_OCMode = TIM_OCMode_PWM1; //Lua chon che do hoat dong
	pwmInit.TIM_OCPolarity = TIM_OCPolarity_High; //
	pwmInit.TIM_Pulse = (10*10000)/100;
	pwmInit.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &pwmInit);
	
	/* Ch3 with duty 40 % */
//	pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
//	pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
//	pwmInit.TIM_Pulse = (40*10000)/100;
//	pwmInit.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OC3Init(TIM2, &pwmInit);

	/* Ch1 with duty 80 % */
//	pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
//	pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
//	pwmInit.TIM_Pulse = (80*10000)/100;
//	pwmInit.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OC4Init(TIM2, &pwmInit);
}

int main() {
	PWM_StandardLibrary();
	while(1) {
		for(uint16_t i = 0; i < 9999; i++) {
			TIM_SetCompare2(TIM2,i);
			i++;
			Delay_ms(1);
		}
	}
}
	
		