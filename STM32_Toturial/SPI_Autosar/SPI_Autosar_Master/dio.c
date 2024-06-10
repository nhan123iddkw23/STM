#include <dio.h>

void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level) {
	   GPIO_TypeDef* gpio;
	   uint16_t gpioPin;
	   switch(ChannelId) {
			 case DIO_CHANNEL_PA0:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PA1:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PA2:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PA3:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PA4:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PA5:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PA6:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PA7:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PA8:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PA9:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PA10:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PA11:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PA12:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PA13:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PA14:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PA15:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 case DIO_CHANNEL_PB0:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PB1:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PB2:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PB3:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PB4:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PB5:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PB6:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PB7:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PB8:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PB9:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PB10:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PB11:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PB12:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PB13:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PB14:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PB15:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 
			 case DIO_CHANNEL_PC13:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PC14:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PC15:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
		 }
		 if(Level == STD_HIGH) {
			 GPIO_SetBits(gpio,gpioPin);
		 }
		 else{
			 GPIO_ResetBits(gpio,gpioPin);
		 }		 
}

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	   GPIO_TypeDef* gpio;
	   uint16_t gpioPin;
	   switch(ChannelId) {
			 case DIO_CHANNEL_PA0:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PA1:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PA2:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PA3:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PA4:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PA5:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PA6:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PA7:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PA8:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PA9:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PA10:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PA11:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PA12:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PA13:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PA14:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PA15:
			 {
				 gpio = GPIOA;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 case DIO_CHANNEL_PB0:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_0;
				 break;
			 }
			 case DIO_CHANNEL_PB1:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_1;
				 break;
			 }
			 case DIO_CHANNEL_PB2:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_2;
				 break;
			 }
			 case DIO_CHANNEL_PB3:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_3;
				 break;
			 }
			 case DIO_CHANNEL_PB4:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_4;
				 break;
			 }
			 case DIO_CHANNEL_PB5:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_5;
				 break;
			 }
			 case DIO_CHANNEL_PB6:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_6;
				 break;
			 }
			 case DIO_CHANNEL_PB7:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_7;
				 break;
			 }
			 case DIO_CHANNEL_PB8:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_8;
				 break;
			 }
			 case DIO_CHANNEL_PB9:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_9;
				 break;
			 }
			 case DIO_CHANNEL_PB10:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_10;
				 break;
			 }
			 case DIO_CHANNEL_PB11:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_11;
				 break;
			 }
			 case DIO_CHANNEL_PB12:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_12;
				 break;
			 }
			 case DIO_CHANNEL_PB13:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PB14:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PB15:
			 {
				 gpio = GPIOB;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
			 
			 case DIO_CHANNEL_PC13:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_13;
				 break;
			 }
			 case DIO_CHANNEL_PC14:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_14;
				 break;
			 }
			 case DIO_CHANNEL_PC15:
			 {
				 gpio = GPIOC;
				 gpioPin = GPIO_Pin_15;
				 break;
			 }
		 }
		 if(GPIO_ReadInputDataBit(gpio,gpioPin) == 0) {
			 return STD_HIGH;
		 }
		 else {
			 return STD_LOW;
		 }
	 }
