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
#include "stm32f10x_dma.h"
#include "delay.h"


#define SPIx_RCC      RCC_APB1Periph_SPI2
#define SPIx          SPI2
#define SPI_GPIO_RCC  RCC_APB2Periph_GPIOB
#define SPI_GPIO      GPIOB
#define LED           GPIOA
#define SPI_PIN_MOSI  GPIO_Pin_15
#define SPI_PIN_MISO  GPIO_Pin_14
#define SPI_PIN_SCK   GPIO_Pin_13
#define SPI_PIN_SS    GPIO_Pin_12


void SPIx_Init(void);
void GPIO_Configuration(void); 
volatile uint16_t  data[10];
void TIMER_Config();


int main(void)
{  
	GPIO_Configuration();
	SPIx_Init();
	TIMER_Config();
	while(1) {
		TIM_SetCompare1(TIM1,9000);
	}
	
}


/*
* Function: SPIx_Init
* Description: Ham cau hinh SPI,DMA
* Input:
*   none
* Output:
*   none
*/
void SPIx_Init()
{
    // Init struct
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	  DMA_InitTypeDef DMA_Struct;
    SPI_InitTypeDef SPI_InitStruct;
    

    //Init SPI
    RCC_APB1PeriphClockCmd(SPIx_RCC, ENABLE);
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//72Mhs/16
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;//0b001001001
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);
	
	
	 // Init DMA
	 DMA_Struct.DMA_BufferSize = 1;
	 DMA_Struct.DMA_DIR        = DMA_DIR_PeripheralSRC;
	 DMA_Struct.DMA_M2M        = DMA_M2M_Disable;
	 DMA_Struct.DMA_MemoryBaseAddr = (uint32_t)data;
	 DMA_Struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	 DMA_Struct.DMA_MemoryInc      = DMA_MemoryInc_Enable;
	 DMA_Struct.DMA_Mode           = DMA_Mode_Normal;
	 DMA_Struct.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	 DMA_Struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	 DMA_Struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	 DMA_Struct.DMA_Priority = DMA_Priority_Medium;
	 DMA_Init(DMA1_Channel4,&DMA_Struct);
	 DMA_Cmd(DMA1_Channel4,ENABLE);
	 SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE);
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
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
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
	
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED, &GPIO_InitStruct);
}



void TIMER_Config(){
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	 TIM_TimeBaseInitTypeDef  Time_BaseStructInit;
	 Time_BaseStructInit.TIM_Period = 20000-1;
	 Time_BaseStructInit.TIM_Prescaler = 720-1;
	 Time_BaseStructInit.TIM_ClockDivision = 0;
	 Time_BaseStructInit.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseInit(TIM1,&Time_BaseStructInit);
	
	 
	 TIM_OCInitTypeDef        TIM_OCInitStructure;
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = 10000;
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
   TIM_ARRPreloadConfig(TIM1, ENABLE);

   TIM_Cmd(TIM1,ENABLE);
	 
}


