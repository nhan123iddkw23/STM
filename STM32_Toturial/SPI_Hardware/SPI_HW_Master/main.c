#include <stm32f10x.h>
#include <delay.h>

void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef SPI;
	// SS
	SPI.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI.GPIO_Pin = GPIO_Pin_12;
	SPI.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&SPI);
	// CLK
	SPI.GPIO_Mode = GPIO_Mode_AF_PP;
	SPI.GPIO_Pin = GPIO_Pin_13;
	SPI.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&SPI);
	// MISO
	SPI.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	SPI.GPIO_Pin = GPIO_Pin_14;
	SPI.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&SPI);
	// MOSI
	SPI.GPIO_Mode = GPIO_Mode_AF_PP;
	SPI.GPIO_Pin = GPIO_Pin_15;
	SPI.GPIO_Speed =GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&SPI);
	
}

void config1() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef Slave;
	// SS
	Slave.GPIO_Mode = GPIO_Mode_AF_PP;
	Slave.GPIO_Pin = GPIO_Pin_15;
	Slave.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&Slave);
	// CLK
}

void config_SPI_Master() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	SPI_InitTypeDef spi;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2,&spi);
	SPI_Cmd(SPI2,ENABLE);
}

int main() {
	config();
	config_SPI_Master();
	while(1) {
//		GPIO_ResetBits(GPIOB,GPIO_Pin_12); //  chan ss len muc 1
//		SPI_I2S_SendData(SPI2,0x00);
//		while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == SET) {
//		} // cho truyen xong
//		GPIO_SetBits(GPIOB,GPIO_Pin_12);// chan ss xuong muc 0
//		Delay_ms(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12); //  chan ss len muc 1
		SPI_I2S_SendData(SPI2,0x38);
		while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == SET) {
		} // cho truyen xong
		GPIO_SetBits(GPIOB,GPIO_Pin_12);// chan ss xuong muc 0
		Delay_ms(500);
   }
}