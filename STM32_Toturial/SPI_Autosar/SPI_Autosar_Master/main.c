#include <stm32f10x.h>
#include <delay.h>
#include <dio.h>
typedef struct {
	uint16_t  SPI_BaudRatePrescaler;
	uint16_t  SPI_CPHA;
	uint16_t  SPI_CPOL ;
	uint16_t  SPI_CRCPolynomial ;
	uint16_t  SPI_DataSize ;
	uint16_t  SPI_Direction ;
	uint16_t  SPI_FirstBit ;
	uint16_t  SPI_Mode ;
	uint16_t  SPI_NSS ;
}Spi_ConfigType;

typedef uint8_t Std_ReturnType;
typedef uint8_t Spi_ChannelType;
typedef uint8_t Spi_DataBufferType;

#define spi1 (Spi_ChannelType)1
#define spi2 (Spi_ChannelType)2
#define E_OK (Std_ReturnType)0
#define E_NOT_OK (Std_ReturnType)1

void config_GPIOC() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	 GPIO_InitTypeDef gpioc; 
	 gpioc.GPIO_Mode = GPIO_Mode_Out_PP;
	 gpioc.GPIO_Pin = GPIO_Pin_13;
	 gpioc.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOC,&gpioc);
}

void config_GPIOA() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  // CS
	 GPIO_InitTypeDef gpioa; 
	 gpioa.GPIO_Mode = GPIO_Mode_Out_PP;
	 gpioa.GPIO_Pin = GPIO_Pin_4;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa);
	 // CLK
	 gpioa.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpioa.GPIO_Pin = GPIO_Pin_5;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa);
	 // MOSI 
	 gpioa.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpioa.GPIO_Pin = GPIO_Pin_6;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa);
	 // MISO
	 gpioa.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 gpioa.GPIO_Pin = GPIO_Pin_7;
	 gpioa.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOA,&gpioa); 
}

void config_GPIOB() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  // CS
	 GPIO_InitTypeDef gpiob; 
	 gpiob.GPIO_Mode = GPIO_Mode_Out_PP;
	 gpiob.GPIO_Pin = GPIO_Pin_12;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 // CLK
	 gpiob.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpiob.GPIO_Pin = GPIO_Pin_13;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 // MOSI 
	 gpiob.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpiob.GPIO_Pin = GPIO_Pin_14;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 // MISO
	 gpiob.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 gpiob.GPIO_Pin = GPIO_Pin_15;
	 gpiob.GPIO_Speed = GPIO_Speed_2MHz;
	 GPIO_Init(GPIOB,&gpiob);
	 
	 
}


void Spi_Init () { //const
	  Spi_ConfigType* ConfigPtr;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	  ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	  ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge;
	  ConfigPtr->SPI_CPOL = SPI_CPOL_High;
	  ConfigPtr->SPI_DataSize = SPI_DataSize_8b;
	  ConfigPtr->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	  ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB;
	  ConfigPtr->SPI_Mode = SPI_Mode_Master;
	  ConfigPtr->SPI_NSS = SPI_NSS_Soft;
	  SPI_Init(SPI2,&ConfigPtr);
	  SPI_Cmd(SPI2,ENABLE);
}


Std_ReturnType Spi_DeInit (void) {
	if(spi1) {
	SPI_Cmd(SPI1,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE);
	return E_OK;
  }
	if(spi2) {
	SPI_Cmd(SPI2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
	return E_OK;
  }
	return E_NOT_OK;
}
	
uint8_t data[4]={0x4E,0x48,0x41,0x4E};//,0x48,0x41,0x4E};
	
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr) {
	  switch(Channel) {
			case spi1: {
				config_GPIOA();
				Dio_WriteChannel(DIO_CHANNEL_PA4,STD_LOW);
        for(int i = 0; i<sizeof(DataBufferPtr); i++){
		    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	      SPI_I2S_SendData(SPI1,*DataBufferPtr++);
	      while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY) == RESET);
				}
		    Dio_WriteChannel(DIO_CHANNEL_PA4,STD_HIGH); 
			return E_OK;
		}
		break;
			case spi2: {
				config_GPIOB();
	     Dio_WriteChannel(DIO_CHANNEL_PB12,STD_LOW);
				for(int i = 0; i<sizeof(DataBufferPtr); i++){
		    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	      SPI_I2S_SendData(SPI2,*DataBufferPtr++);
	      while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == RESET);
				}
		    Dio_WriteChannel(DIO_CHANNEL_PB12,STD_HIGH); 
			return E_OK;
	        }
			break;
        }
		return E_NOT_OK;
		}

Std_ReturnType Spi_ReadIB ( Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer) {
	  switch (Channel) {
			case spi1: {
				config_GPIOA();
				for(int i = 0; i < sizeof(DataBufferPointer); i++) {
				while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
				*DataBufferPointer++ = SPI_I2S_ReceiveData(SPI1);
				while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY) == RESET);
				}
				return E_OK;
			  }
			 break;
			case spi2: {
				config_GPIOB();
				for(int i = 0; i < sizeof(DataBufferPointer); i++) {
				while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET);
				*DataBufferPointer++ = SPI_I2S_ReceiveData(SPI2);
				while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY) == RESET);
				}
				return E_OK;
				break;
			  }
		}
		return E_NOT_OK;
	}

int main() {
			Spi_Init ();
	   while(1) {
			if(Spi_WriteIB(spi2,data) == E_OK) {
				config_GPIOC();
				Dio_WriteChannel(DIO_CHANNEL_PC13,STD_LOW);
				Delay_ms(1000);
				Dio_WriteChannel(DIO_CHANNEL_PC13,STD_HIGH);
				Delay_ms(200);
		 }
	}
}

	