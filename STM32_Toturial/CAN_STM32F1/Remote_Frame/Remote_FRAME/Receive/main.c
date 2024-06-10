#include <stm32f10x.h>

uint8_t testArray[8] = {1,7,0,6,2,0,0,3};

void Config_GPIO() {
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

void Config_CAN1(uint32_t id) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	CAN_InitTypeDef can;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TTCM = DISABLE;
	can.CAN_TXFP = DISABLE;
	can.CAN_Mode = CAN_Mode_Normal;
	
	can.CAN_SJW = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_3tq;
	can.CAN_BS2 = CAN_BS2_5tq;
	can.CAN_Prescaler  = 4;
	 
	CAN_Init(CAN1,&can);
	
	CAN_FilterInitTypeDef canFilter;
	canFilter.CAN_FilterNumber = 0;
	canFilter.CAN_FilterScale = CAN_FilterScale_32bit;
	canFilter.CAN_FilterMode = CAN_FilterMode_IdMask;
	canFilter.CAN_FilterIdHigh = (id<<5);
	canFilter.CAN_FilterIdLow = 0x0000;
	canFilter.CAN_FilterMaskIdHigh = 0xFFFF;
	canFilter.CAN_FilterMaskIdLow = 0x0000;
	canFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	canFilter.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&canFilter);
}

void Feedback_Pressure(uint8_t *data,uint8_t len, uint32_t id) {
	 CanRxMsg RxMessage;
	 CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	 while((RxMessage.StdId == 0x123 && RxMessage.RTR == CAN_RTR_REMOTE) == 0);
	 CanTxMsg TxMessage;
	 TxMessage.DLC = len;
	 TxMessage.ExtId = 0x00;
	 TxMessage.IDE = CAN_ID_STD;
	 TxMessage.RTR = CAN_RTR_DATA;
	 TxMessage.StdId = id;
	 for(int i = 0; i < TxMessage.DLC; i++) {
		 TxMessage.Data[i] = data[i];
	 }
	 CAN_Transmit(CAN1,&TxMessage);
 }

int main() {
	Config_GPIO();
	Config_CAN1(0x123);
	Feedback_Pressure(testArray,8,0x0000);
}

