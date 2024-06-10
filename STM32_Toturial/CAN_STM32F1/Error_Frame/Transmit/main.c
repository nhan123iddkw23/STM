#include <stm32f10x.h>
#include <stdio.h>

struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};

int fputc(int ch, FILE *f) {
	ITM_SendChar(ch);//send method for SWV
	return(ch);
}

void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

uint8_t testArray[8] = {'L','i','n','h',0,0,0,0};
void gpio_Config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  GPIO_InitTypeDef GPIO_INITSTRUCT;
	  GPIO_INITSTRUCT.GPIO_Mode = GPIO_Mode_IPU;
	  GPIO_INITSTRUCT.GPIO_Pin  = GPIO_Pin_11;
	  GPIO_INITSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_INITSTRUCT.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_INITSTRUCT.GPIO_Pin = GPIO_Pin_12;
	  GPIO_INITSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	  
	  GPIO_Init(GPIOA,&GPIO_INITSTRUCT);
}

void can_Config() {
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	 CAN_InitTypeDef Can;
	 Can.CAN_ABOM = DISABLE;
	 Can.CAN_AWUM = DISABLE;
	 Can.CAN_NART = DISABLE;
	 Can.CAN_RFLM = DISABLE;
	 Can.CAN_TTCM = DISABLE;
	 Can.CAN_TXFP = DISABLE;
	 Can.CAN_Mode = CAN_Mode_Normal;
	 
	 Can.CAN_SJW = CAN_SJW_1tq;
	 Can.CAN_BS1 = CAN_BS1_3tq;
	 Can.CAN_BS2 = CAN_BS2_5tq;
	 Can.CAN_Prescaler = 4;
	 CAN_Init(CAN1,&Can);
	
	 CAN_FilterInitTypeDef CanFilter;
	 CanFilter.CAN_FilterNumber = 0;
	 CanFilter.CAN_FilterScale = CAN_FilterScale_32bit;
	 CanFilter.CAN_FilterMode  = CAN_FilterMode_IdMask;
	 CanFilter.CAN_FilterIdHigh = 0X0000;
	 CanFilter.CAN_FilterIdLow = 0X0000;
	 CanFilter.CAN_FilterMaskIdHigh = 0X0000;
	 CanFilter.CAN_FilterMaskIdLow = 0X0000;
	 CanFilter.CAN_FilterFIFOAssignment = CAN_FIFO0;
	 CanFilter.CAN_FilterActivation = ENABLE;
	 CAN_FilterInit(&CanFilter);
 }

void Send_Data_Message(uint8_t *data, uint8_t len, uint32_t id) {
	 CanTxMsg TxMessage;
	 TxMessage.DLC = len;
	 TxMessage.ExtId = 0x00;
	 TxMessage.IDE = CAN_ID_STD;
	 TxMessage.RTR = CAN_RTR_DATA;
	 TxMessage.StdId = id;
	 for(int i = 0; i < TxMessage.DLC; i++) {
		  TxMessage.Data[i] = testArray[i];
	 }
	 
	 CAN_Transmit(CAN1,&TxMessage);
	 if(CAN_Transmit(CAN1,&TxMessage) != CAN_TxStatus_Ok) {
		 printf("Error Frame");
	 }
 }

int main() {
	gpio_Config();
	can_Config();
	while(1) {
		Send_Data_Message(testArray,8,0x117);
		printf("DATA Frame");
	}
}


