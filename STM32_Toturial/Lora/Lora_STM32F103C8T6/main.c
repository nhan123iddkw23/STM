#include "stm32f10x.h"
#include <delay.h>
#include <LoRa.h>
void GPIO_Config();
void SPI1_Config();
void SPI2_Config();
void EXTI0_Config(void);
LoRa myLoRa;
uint8_t read_data[128];
uint8_t send_data[128];
int			RSSI;


void EXTI1_IRQHandler()
{	
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	 {
     LoRa_receive(&myLoRa, read_data, 10);
	 }
	 EXTI_ClearITPendingBit(EXTI_Line1);
}


int main(){
	GPIO_Config();
	EXTI0_Config();
	SPI1_Config();
	SPI2_Config();
	Init_TIMER();
	send_data[0] = 'M';
	send_data[1] = 'i';
	send_data[2] = 'n';
	send_data[3] = 'h';
	send_data[4] = 'N';
	send_data[5] = 'h';
	send_data[6] = 'a';
	send_data[7] = 'n';
	
	myLoRa.hSPIx                 = SPI2;
	myLoRa.CS_port               = GPIOB;
	myLoRa.CS_pin                = GPIO_Pin_12;
	myLoRa.reset_port            = GPIOB;
	myLoRa.reset_pin             = GPIO_Pin_0;
	myLoRa.DIO0_port						 = GPIOB;
	myLoRa.DIO0_pin							 = GPIO_Pin_1;
	
	myLoRa.frequency             = 433;							  // default = 433 MHz
	myLoRa.spredingFactor        = SF_7;							// default = SF_7
	myLoRa.bandWidth			       = BW_125KHz;				  // default = BW_125KHz
	myLoRa.crcRate				       = CR_4_5;						// default = CR_4_5
	myLoRa.power					       = POWER_20db;				// default = 20db
	myLoRa.overCurrentProtection = 120; 							// default = 100 mA
	myLoRa.preamble				       = 10;		  					// default = 8;
	
	LoRa_reset(&myLoRa);
	LoRa_init(&myLoRa);
	LoRa_startReceiving(&myLoRa);
	while(1){
    LoRa_transmit(&myLoRa, (uint8_t*)send_data, 8, 100);
		Delay_ms(500);
	}
}


void GPIO_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // BUTTON
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void EXTI0_Config(void)
 {
   /* Enable GPIOA clock */
	 GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   /* Configure PA.00 pin as input floating */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
 
   /* Enable AFIO clock */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
   EXTI_InitTypeDef EXTI_InitStructure;
   /* Connect EXTI0 Line to PA.00 pin */
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
 
   /* Configure EXTI0 line */
   EXTI_InitStructure.EXTI_Line = EXTI_Line1;
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStructure);
 
   NVIC_InitTypeDef NVIC_InitStructure;
   /* Enable and set EXTI0 Interrupt to the lowest priority */
   NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
 }

void SPI1_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //NSS
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //CLK
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // MISO
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         // MOSI
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	SPI_InitTypeDef SPI_InitStructure;
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI1, &SPI_InitStructure);
	 SPI_Cmd(SPI1,ENABLE);
}


void SPI2_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //NSS
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //CLK
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         // MOSI
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         // MOSI
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	SPI_InitTypeDef SPI_InitStructure;
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI2, &SPI_InitStructure);
	 SPI_Cmd(SPI2,ENABLE);
}




