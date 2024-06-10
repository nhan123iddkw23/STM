#include <stm32f10x.h>

uint8_t testArray0[8];

uint8_t testArray1[8];

void gpio_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	
	
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_12;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpio);
}

void can_Init(uint32_t id) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	CAN_InitTypeDef  CanInitStruct;
	CanInitStruct.CAN_TTCM = DISABLE;
	CanInitStruct.CAN_TXFP = DISABLE;
	CanInitStruct.CAN_ABOM = DISABLE;
	CanInitStruct.CAN_AWUM = DISABLE;
	CanInitStruct.CAN_RFLM = DISABLE;
	CanInitStruct.CAN_NART = DISABLE;
	CanInitStruct.CAN_Mode = CAN_Mode_Normal;
	
	CanInitStruct.CAN_SJW = CAN_SJW_1tq;
	CanInitStruct.CAN_BS1 = CAN_BS1_3tq;
	CanInitStruct.CAN_BS2 = CAN_BS2_5tq;
	CanInitStruct.CAN_Prescaler = 4;
	CAN_Init(CAN1,&CanInitStruct);
	
	CAN_FilterInitTypeDef CanFilter;
	CanFilter.CAN_FilterNumber  = 0;
	CanFilter.CAN_FilterScale = CAN_FilterScale_32bit;
	CanFilter.CAN_FilterMode = CAN_FilterMode_IdMask;
	CanFilter.CAN_FilterIdHigh = (id<<5);
	CanFilter.CAN_FilterIdLow = 0x0000;
	CanFilter.CAN_FilterMaskIdHigh = 0xFFFF;
	CanFilter.CAN_FilterMaskIdLow = 0x0000;
	CanFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CanFilter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CanFilter);
	
	CanFilter.CAN_FilterNumber  = 1;
	CanFilter.CAN_FilterScale = CAN_FilterScale_32bit;
	CanFilter.CAN_FilterMode = CAN_FilterMode_IdMask;
	CanFilter.CAN_FilterIdHigh = (0x456<<5);
	CanFilter.CAN_FilterIdLow = 0x0000;
  CanFilter.CAN_FilterMaskIdHigh = 0xFFFF;
	CanFilter.CAN_FilterMaskIdLow = 0x0000;
	CanFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CanFilter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CanFilter);
}

void Receive_Can_Message() {
	CanRxMsg RxMessage;
	while(CAN_MessagePending(CAN1,CAN_FIFO0) < 1) {
	}
	 CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	  if(RxMessage.StdId == 0x123) {
	     for(int i = 0; i < RxMessage.DLC; i++) {
		      testArray0[i] = RxMessage.Data[i];
			 }
		 }
		if(RxMessage.StdId == 0x456) {
			for(int i = 0; i < RxMessage.DLC; i++) {
		      testArray1[i] = RxMessage.Data[i];
		 }
		}
 }

int main() {
	gpio_Init();
	can_Init(0x123);
	while(1) {
		Receive_Can_Message();
	}
}


