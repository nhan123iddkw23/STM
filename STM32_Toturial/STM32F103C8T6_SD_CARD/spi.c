#include "spi.h"

void My_SPI_Init(void)
{
	GPIO_InitTypeDef gpioInit;
	SPI_InitTypeDef   SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpioInit.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &gpioInit);
	
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOB, &gpioInit);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	
	gpioInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_14;
	GPIO_Init(GPIOB, &gpioInit);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);
}

uint8_t My_SPI_Exchange(uint8_t u8Data)
{
 GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	SPI_I2S_SendData(SPI2, u8Data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
	}
 GPIO_SetBits(GPIOB, GPIO_Pin_12);
	return SPI_I2S_ReceiveData(SPI2);
}
