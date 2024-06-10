#include <stm32f10x.h>
#include <delay.h>
uint16_t getData;
uint8_t data = 50;
void GPIO_Config() {
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

void ADC_Config(){
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	 
	  
	  ADC_InitTypeDef adc;
	  adc.ADC_ContinuousConvMode = ENABLE;
	  adc.ADC_DataAlign          = ADC_DataAlign_Right;
	  adc.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None ;
	  adc.ADC_Mode               = ADC_Mode_Independent;
	  adc.ADC_NbrOfChannel       = ADC_Channel_0;
	  adc.ADC_ScanConvMode       = DISABLE;
	  ADC_Init(ADC1,&adc);
	  ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	  ADC_Cmd(ADC1,ENABLE);
	  ADC_ResetCalibration(ADC1);
	  while(ADC_GetResetCalibrationStatus(ADC1));
	  ADC_StartCalibration(ADC1);
	  while(ADC_GetCalibrationStatus(ADC1));
	  ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void config1() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	// SS
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Speed =GPIO_Speed_2MHz;
	
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&gpio);
	// CLK
}

void SPI_Master_Config() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
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
}

int main() {
	GPIO_Config();
	ADC_Config();
	SPI_Master_Config();
	while(1) {
		
		
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_12); //  chan ss len muc 1
		SPI_I2S_SendData(SPI2,data);
		while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == SET) {
		} // cho truyen xong
		GPIO_SetBits(GPIOB,GPIO_Pin_12);// chan ss xuong muc 0	
     getData =  ADC_GetConversionValue(ADC1);
		Delay_ms(300);
   }
}