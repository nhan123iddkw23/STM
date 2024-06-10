/*
* File: dio.h
* Author: Hoang Minh Nhan
* Date: 29/05/2023
* Description: Day la file .h
*/
#ifndef __DIO_H
#define __DIO_H
#include <stm32f10x.h>
	typedef enum{
	DIO_CHANNEL_PA5,
	DIO_CHANNEL_PA6,
	DIO_CHANNEL_PA7,
	DIO_CHANNEL_PB5,
	DIO_CHANNEL_PB6,
	DIO_CHANNEL_PB7,
	DIO_CHANNEL_PC13
}Dio_ChannelType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_LevelType;
void config();
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void delay();
void BlinkLED();
void LED();
void LED1();
void program();
#endif