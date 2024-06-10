#include <stm32f10x.h>
#include <delay.h>

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

void can_Init() {
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
	CanFilter.CAN_FilterIdHigh = 0x0000;
	CanFilter.CAN_FilterIdLow = 0x0000;
	CanFilter.CAN_FilterMaskIdHigh = 0x0000;
	CanFilter.CAN_FilterMaskIdLow = 0x0000;
	CanFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CanFilter.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&CanFilter);
}

void Send_Data(uint8_t *data, uint8_t len, uint32_t id) {
	   CanTxMsg CanMessage;
	
	   CanMessage.DLC = len;
	   CanMessage.ExtId = 0x00;
	   CanMessage.IDE = CAN_ID_STD;
	   CanMessage.RTR = CAN_RTR_DATA;
	   CanMessage.StdId = id;
	   for(int i = 0; i < len ; i++) {
			 CanMessage.Data[i] = data[i];
		 }
		 CAN_Transmit(CAN1,&CanMessage);
	 }

	 int main() {
		 gpio_Init();
		 can_Init();
		 uint8_t data[8] = {'m','i','n','h','n','h','a','n'};
		 uint8_t data1[8] = {1,7,0,6,2,0,0,3};
		 while(1) {
		Send_Data(data,8,0x123);
	  Delay_ms(10);
		Send_Data(data1,8,0x456);
		Delay_ms(10);
		 }
	 }
	
	