#include <stm32f10x.h>
#include <delay.h>
#include <lcd.h>


static uint16_t x = 0;


void config_gpio() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&gpio);
	}

void config_adc() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	ADC_InitTypeDef adc;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_ScanConvMode = DISABLE;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_NbrOfChannel = 1;
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
		x = ADC_GetConversionValue(ADC1);
		Delay_ms(500);
		LCD_Gotoxy(0,0);
		LCD_Puts("Value of ADC");
		LCD_Gotoxy(0,1);
		LCD_Number(x);
		}
	}

