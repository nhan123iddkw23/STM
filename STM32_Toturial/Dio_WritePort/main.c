#include <stm32f10x.h>

void config() {
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	   GPIO_InitTypeDef LED7;
	   LED7.GPIO_Mode = GPIO_Mode_Out_PP;
	   LED7.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	   LED7.GPIO_Speed = GPIO_Speed_2MHz;
	   GPIO_Init(GPIOA,&LED7);
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	   GPIO_InitTypeDef BUTTON;
	   BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	   BUTTON.GPIO_Pin = GPIO_Pin_0;
	   BUTTON.GPIO_Speed = GPIO_Speed_2MHz;
	   GPIO_Init(GPIOB,&BUTTON);
	 }

void delay() {
	  for(uint32_t i = 0;i<1000000;i++){
			for(uint64_t j = 0;i<1000000;i++);
	 }
}

typedef enum{
	 DIO_CHANNEL_PA0,
	 DIO_CHANNEL_PA1,
	 DIO_CHANNEL_PA2,
	 DIO_CHANNEL_PA3,
	 DIO_CHANNEL_PA4,
	 DIO_CHANNEL_PA5,
	 DIO_CHANNEL_PA6,
	 DIO_CHANNEL_PA7,
	 DIO_CHANNEL_PA8,
	 DIO_CHANNEL_PA9,
	 DIO_CHANNEL_PA10,
	 DIO_CHANNEL_PA11,
	 DIO_CHANNEL_PA12,
	 DIO_CHANNEL_PA13,
	 DIO_CHANNEL_PA14,
	 DIO_CHANNEL_PA15,
	 DIO_CHANNEL_PB0,
	 DIO_CHANNEL_PB1,
	 DIO_CHANNEL_PB2,
	 DIO_CHANNEL_PB3,
	 DIO_CHANNEL_PB4,
	 DIO_CHANNEL_PB5,
	 DIO_CHANNEL_PB6,
	 DIO_CHANNEL_PB7,
	 DIO_CHANNEL_PB8,
	 DIO_CHANNEL_PB9,
	 DIO_CHANNEL_PB10,
	 DIO_CHANNEL_PB11,
	 DIO_CHANNEL_PB12,
	 DIO_CHANNEL_PB13,
	 DIO_CHANNEL_PB14,
	 DIO_CHANNEL_PB15,
	 DIO_CHANNEL_PC13,
	 DIO_CHANNEL_PC14,
	 DIO_CHANNEL_PC15
	}Dio_ChannelType ;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;
	
typedef enum{
	PortA,
	PortB,
	PortC
}Dio_PortType;

typedef struct{
	uint16_t bit_16;
}Dio_PortLevelType;


void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);


	 
void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level) {
	   GPIO_TypeDef * gpioPort;
	   uint16_t gpioPin;
	 switch(ChannelId) {
		 case DIO_CHANNEL_PA0: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_0;
			 break;
			 }
		 case DIO_CHANNEL_PA1: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_1;
			 break;
			 }
		 case DIO_CHANNEL_PA2: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_2;
			 break;
			 }
		 case DIO_CHANNEL_PA3: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_3;
			 break;
			 }
		 case DIO_CHANNEL_PA4: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_4;
			 break;
			 }
		 case DIO_CHANNEL_PA5: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_5;
			 break;
			 }
		 case DIO_CHANNEL_PA6: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_6;
			 break;
			 }
		 case DIO_CHANNEL_PA7: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_7;
			 break;
			 }
		 case DIO_CHANNEL_PA8: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_8;
			 break;
			 }
		 case DIO_CHANNEL_PB0: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_0;
			 break;
			 }
		 case DIO_CHANNEL_PB1: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_1;
			 break;
			 }
		 case DIO_CHANNEL_PB2: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_2;
			 break;
			 }
		 case DIO_CHANNEL_PB3: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_3;
			 break;
			 }
		 case DIO_CHANNEL_PB4: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_4;
			 break;
			 }
		 case DIO_CHANNEL_PB5: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_5;
			 break;
			 }
		 case DIO_CHANNEL_PB6: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_6;
			 break;
			 }
		 case DIO_CHANNEL_PB7: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_7;
			 break;
			 }
		 case DIO_CHANNEL_PB8: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_8;
			 break;
			 }
	    }
	 if(Level == STD_LOW) {
		 GPIO_ResetBits(gpioPort,gpioPin);
	 }
	 else{
		 GPIO_SetBits(gpioPort,gpioPin);
		 }
	 }

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
      GPIO_TypeDef * gpioPort;
	   uint16_t gpioPin;
	 switch(ChannelId) {
		 case DIO_CHANNEL_PA0: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_0;
			 break;
			 }
		 case DIO_CHANNEL_PA1: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_1;
			 break;
			 }
		 case DIO_CHANNEL_PA2: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_2;
			 break;
			 }
		 case DIO_CHANNEL_PA3: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_3;
			 break;
			 }
		 case DIO_CHANNEL_PA4: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_4;
			 break;
			 }
		 case DIO_CHANNEL_PA5: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_5;
			 break;
			 }
		 case DIO_CHANNEL_PA6: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_6;
			 break;
			 }
		 case DIO_CHANNEL_PA7: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_7;
			 break;
			 }
		 case DIO_CHANNEL_PA8: {
			 gpioPort = GPIOA;
			 gpioPin = GPIO_Pin_8;
			 break;
			 }
		 case DIO_CHANNEL_PB0: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_0;
			 break;
			 }
		 case DIO_CHANNEL_PB1: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_1;
			 break;
			 }
		 case DIO_CHANNEL_PB2: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_2;
			 break;
			 }
		 case DIO_CHANNEL_PB3: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_3;
			 break;
			 }
		 case DIO_CHANNEL_PB4: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_4;
			 break;
			 }
		 case DIO_CHANNEL_PB5: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_5;
			 break;
			 }
		 case DIO_CHANNEL_PB6: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_6;
			 break;
			 }
		 case DIO_CHANNEL_PB7: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_7;
			 break;
			 }
		 case DIO_CHANNEL_PB8: {
			 gpioPort = GPIOB;
			 gpioPin = GPIO_Pin_8;
			 break;
			 }
	    }
	 if(GPIO_ReadInputDataBit(gpioPort,gpioPin) == 0) {
		 return STD_LOW;
	 }
	 else{
		 return STD_HIGH;
		 }
	 }

void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level){
		 GPIO_TypeDef * gpioPort;
		 switch(PortId) {
			 case PortA: {
				 gpioPort = GPIOA;
				 GPIO_Write(GPIOA,Level.bit_16);
				 break;
				 }
			 case PortB: {
				 gpioPort = GPIOB;
				 GPIO_Write(GPIOB,Level.bit_16);
				 break;
				 }
			 }
		 }
		 



	 
