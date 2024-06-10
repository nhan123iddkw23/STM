#include "stm32f10x.h"

void Config_led() {
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	   GPIO_InitTypeDef GPIO_Initstruct;
	   GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	   GPIO_Initstruct.GPIO_Pin  = GPIO_Pin_1;
	   GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_Init(GPIOA,&GPIO_Initstruct);
}

void Congfig_EXTI() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	  NVIC_InitTypeDef  nvic;
	  EXTI_InitTypeDef exti;
	  GPIO_EXTILineConfig(GPIOA,GPIO_Pin_0);
	  
	
	  EXTI_ClearITPendingBit(EXTI_Line0);
	 
  	exti.EXTI_Line = EXTI_Line0;
	  exti.EXTI_Mode = EXTI_Mode_Interrupt;
	  exti.EXTI_LineCmd = ENABLE;
	  exti.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_Init(&exti);
	  
	
	  nvic.NVIC_IRQChannel = EXTI0_IRQn;
	  nvic.NVIC_IRQChannelCmd = ENABLE;
	  nvic.NVIC_IRQChannelPreemptionPriority = 0;
	  nvic.NVIC_IRQChannelSubPriority = NVIC_PriorityGroup_0;
	  NVIC_Init(&nvic);
}

void EXTI0_IRQHandler() {
	  if(EXTI_GetFlagStatus(EXTI_Line0) == 1) {
			 EXTI_ClearITPendingBit(EXTI_Line0);
			 GPIO_SetBits(GPIOA,GPIO_Pin_1);
			 for(uint8_t i = 0; i < 255; i++) {
				  for(uint8_t j = 0; j < 255; j++) {
			 }
			 }
		}
}
int main() {
	  Congfig_EXTI();
	  Config_led();
	  while(1) {
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
}

