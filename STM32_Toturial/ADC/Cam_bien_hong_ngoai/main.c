#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"
#include "stdio.h"

uint16_t data;
void config_gpio();
char m[5];
char n[20];
char l[20];

void config_gpio(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	/* Cau hinh A0 */
	
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Pin  = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin  = GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&gpio);
}

void config_adc();
void config_adc(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	/* Cau hinh adc */
	
	ADC_InitTypeDef adc;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Left;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_NbrOfChannel = ADC_Channel_0;
	adc.ADC_ScanConvMode = DISABLE;
	
	ADC_Init(ADC1,&adc);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

int main() {
	 config_gpio();
   config_adc();
	 LCD_Init();
	 while(1) {
		 data = ADC_GetConversionValue(ADC1);
		 Delay_ms(1);
		 if(data >= 10000) {
			 GPIO_SetBits(GPIOB,GPIO_Pin_1);
			 LCD_Gotoxy(0,0);
			 sprintf(&m[0],"%5d",data);
			 LCD_Puts(&m[0]);
			 LCD_Gotoxy(0,1);
			sprintf(&n[0],"%s","Khong vat can");
			 LCD_Puts(&n[0]);
		 }
		 else{
		 GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		 LCD_Gotoxy(0,0);
		 sprintf(&m[0],"%5d",data);
		 LCD_Puts(&m[0]);
		 LCD_Gotoxy(0,1);
		 sprintf(&l[0],"%s","Vat can");
		 LCD_Puts(&l[0]);
		 } 
	 }
 }
			 
	
