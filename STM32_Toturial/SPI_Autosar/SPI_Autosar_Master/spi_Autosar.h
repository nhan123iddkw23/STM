
#ifndef __SPI_H
#define __SPI_H
#include <stm32f10x.h>
 
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

void Spi_Init ();
Std_ReturnType Spi_DeInit (void);
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr);
Std_ReturnType Spi_ReadIB ( Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer);

#endif