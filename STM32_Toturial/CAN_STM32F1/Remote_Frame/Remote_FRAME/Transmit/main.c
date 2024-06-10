#include <stm32f10x.h>


uint8_t testArray[8];
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

void Config_CAN1() {
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
	canFilter.CAN_FilterIdHigh = 0x0000;
	canFilter.CAN_FilterIdLow = 0x0000;
	canFilter.CAN_FilterMaskIdHigh = 0x0000;
	canFilter.CAN_FilterMaskIdLow = 0x0000;
	canFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	canFilter.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&canFilter);
	
}

void Remote_Data(uint32_t id) {
	 CanTxMsg TxMessage;
	 TxMessage.StdId = id;
	 TxMessage.DLC = 0;
	 TxMessage.IDE = CAN_ID_STD;
	 TxMessage.RTR = CAN_RTR_REMOTE;
	 TxMessage.ExtId = 0x00;
	 CAN_Transmit(CAN1,&TxMessage);
	while(CAN_TransmitStatus(CAN1,CAN_FIFO0) != CAN_TxStatus_Ok);
}

void Receive_Data_Message(){
	 CanRxMsg RxMessage;
	 
	  while(CAN_MessagePending(CAN1,CAN_FIFO0));
	  CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	 for(int i = 0; i < RxMessage.DLC;i++) {
		  testArray[i] = RxMessage.Data[i];
	 }
 }

 int main() {
	 Config_GPIO();
	 Config_CAN1();
	 Remote_Data(0x123);
	 while(1) {
		 Receive_Data_Message();
	 }
 }
 
	