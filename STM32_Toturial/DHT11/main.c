#include <stm32f10x.h>

void config_gpio();
void config_tim();
void Delay_us(uint16_t delay_us);

int main() {
	   config_gpio();
	   config_tim();
	while(1) {
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_us(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_us(500);
		}
	}

void config_gpio(){
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	    GPIO_InitTypeDef gpio;
	    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	   gpio.GPIO_Pin =GPIO_Pin_12;
	   gpio.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOB,&gpio);
}

void config_tim(){	
	    TIM_TimeBaseInitTypeDef tim;
	    tim.TIM_CounterMode = TIM_CounterMode_Up;
	    tim.TIM_Period      =  0xFFFF;
	    tim.TIM_Prescaler   = 71;
	   TIM_TimeBaseInit(TIM2,&tim);
	}

void Delay_us(uint16_t delay_us) {
	   for(uint16_t i = 0; i < delay_us; i++) {
		 TIM_Cmd(TIM2,ENABLE);
		 TIM_SetCounter(TIM2,0);
	   while(TIM_GetCounter(TIM2) < 1); 
		 TIM_Cmd(TIM2,DISABLE);
		}
	}