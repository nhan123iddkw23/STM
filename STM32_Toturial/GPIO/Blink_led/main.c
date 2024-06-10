#include <stm32f10x.h>


void Delay(void);
void Led_Init(void);


int main(){
	  Led_Init();
	  while(1){
			 GPIO_SetBits(GPIOC,GPIO_Pin_13);
			 Delay();
			 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			 Delay();
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
	
void Delay(void){
	 for(uint32_t i = 0; i < 0xFFFF; ++i) {
		 }
	}
	