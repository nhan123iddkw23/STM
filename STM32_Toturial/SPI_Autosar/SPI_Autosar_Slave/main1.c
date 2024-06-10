/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 4/07/2023
* Description: Day la file code spi slave
*/

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "delay.h"


#define SPIx_RCC      RCC_APB1Periph_SPI2
#define SPIx          SPI2
#define SPI_GPIO_RCC  RCC_APB2Periph_GPIOB
#define SPI_GPIO      GPIOB
#define SPI_PIN_MOSI  GPIO_Pin_15
#define SPI_PIN_MISO  GPIO_Pin_14
#define SPI_PIN_SCK   GPIO_Pin_13
#define SPI_PIN_SS    GPIO_Pin_12


void NVIC_Configuration(void);
void SPIx_Init(void);
uint8_t SPIx_EnableSlave(void);
void GPIO_Configuration(void); 
volatile uint8_t RxIdx = 0;
volatile uint8_t  data[4]={0x00,0x00,0x00,0x00};

void SPI2_IRQHandler(void)
{
	if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
	{
		data[RxIdx] = SPI_I2S_ReceiveData(SPIx);
    RxIdx++;		
		if(RxIdx>3) {
			RxIdx = 0;
			}
	}
}

int main(void)
{
	  NVIC_Configuration();
    
		SPIx_Init();

    while (1)
    {
			if(SPIx_EnableSlave())
			{
				
			}			
    }
}









/*
* Function: NVIC_Configuration
* Description: Ham cau hinh ngat
* Input:
*   none
* Output:
*   none
*/

void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /*SPI_MASTER interrupt -------------------------------*/
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

/*
* Function: SPIx_Init
* Description: Ham cau hinh SPI 
* Input:
*   none
* Output:
*   none
*/
void SPIx_Init()
{
    // Init struct
    SPI_InitTypeDef SPI_InitStruct;
    

    //Init SPI
    RCC_APB1PeriphClockCmd(SPIx_RCC, ENABLE);
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPIx, &SPI_InitStruct); 
    SPI_Cmd(SPIx, ENABLE);
    SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);
}

/*
* Function: GPIO_Configuration()
* Description: Ham cau hinh GPIO 
* Input:
*   none
* Output:
*   none
*/
void GPIO_Configuration() {
     GPIO_InitTypeDef GPIO_InitStruct;
	   RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
	   GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_SCK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
    // GPIO MISO
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_MISO;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

    // GPIO SS
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
}

/*
* Function: SPIx_EnableSlave()
* Description: Ham kiem tra chan ss 
* Input:
*   none
* Output:
*   return 0 or return 1
*/
uint8_t SPIx_EnableSlave()
{
    // 
    if(SPI_GPIO->IDR & SPI_PIN_SS)
			return 0;
		else
			return 1;
}
