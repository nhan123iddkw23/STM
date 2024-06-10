#include <stm32f10x.h>


void Delay_1_Ms(void);
void Delay_Ms(uint32_t Delay);
void Led_Init(void);


int main(){
	  Led_Init();
	  while(1){
			 GPIO_SetBits(GPIOC,GPIO_Pin_13);
			 Delay_Ms(500);
			 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			 Delay_Ms(500);
			}
	}

void Delay_1_Ms(void){
	  SysTick->LOAD = 72*1000-1;
	  SysTick->VAL  = 0;
	  SysTick->CTRL = 5;
	  while(!(SysTick->CTRL & (1 << 16))){
			}
	}

void Delay_Ms(uint32_t Delay){
	     while(Delay--) {
				  Delay_1_Ms();
			}
	}

void Led_Init(void){
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 
	 GPIO_InitTypeDef GPIO_Init_Struct;
	 
	 GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init_Struct.GPIO_Pin  = GPIO_Pin_13;
	 GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOC,&GPIO_Init_Struct);
	}
	
	