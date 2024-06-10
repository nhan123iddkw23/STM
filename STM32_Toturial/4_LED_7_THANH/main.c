#include <stm32f10x.h>

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
		uint16_t x,x1,x2,x3,x4;
	uint8_t ma_led[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0b01111000,0x80,0x90};
	uint8_t led[4] = {0b00000001,0b0000010,0b00100000,0b01000000};
	int main() {
		config();
		Init_TIMER();
		while(1){
			for(x = 1000; x<10000; x++) {
			   for(int i = 0; i < 250; i++) {
				x1=x/1000;
        x2=(x%1000)/100;
        x3=((x%1000)%100)/10;
        x4=((x%1000)%100)%10; 
			  GPIOB->ODR = led[0];
			  GPIOA->ODR = ma_led[x1];
			  Delay_ms(1);
			  GPIOB->ODR =led[1];
			  GPIOA->ODR = ma_led[x2];
			  Delay_ms(1);
			  GPIOB->ODR =led[2];
			  GPIOA->ODR = ma_led[x3];		
			  Delay_ms(1);
		  	GPIOB->ODR =led[3];
			  GPIOA->ODR = ma_led[x4];
			  Delay_ms(1);
			}
			}
			}
		}