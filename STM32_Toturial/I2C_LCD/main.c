#include <stm32f10x.h>
#include <delay.h>
void config() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	 GPIO_InitTypeDef gpio;
	 gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	 gpio.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	 gpio.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&gpio);
	
	I2C_InitTypeDef I2C;
	I2C.I2C_Mode = I2C_Mode_I2C;
	I2C.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C.I2C_OwnAddress1 = 0;
	I2C.I2C_Ack = I2C_Ack_Disable;
	I2C.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C.I2C_ClockSpeed = 100000;
	I2C_Init(I2C2,&I2C);
	
	I2C_Cmd(I2C2,ENABLE);
}

void Lcd_Write_byte(char data) {
	I2C_GenerateSTART(I2C2,ENABLE);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C2,0X27,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C2,data);
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C2,ENABLE);
}



void Lcd_Data_Write(char data) {
		char data_u, data_l;
	uint8_t data_t[4] , i = 0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x0d;
	data_t[1] = data_u|0x09;
	data_t[2] = data_l|0x0d;
	data_t[3] = data_l|0x09;
	for(i = 0; i < 4; i++) {
		 Lcd_Write_byte(data_t[i]);
	}
}

void lcd_send_string (char *str)
{
	while (*str) Lcd_Data_Write (*str++);
}

void Lcd_Control_Write(char data) {
	char data_u, data_l;
	uint8_t data_t[4] , i = 0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x0C;
	data_t[1] = data_u|0x08;
	data_t[2] = data_l|0x0C;
	data_t[3] = data_l|0x08;
	for(i = 0; i < 4; i++) {
		 Lcd_Write_byte(data_t[i]);
	}
}
	

void Lcd_init() {
	Lcd_Control_Write(0x33);
	Delay_ms(10);
	Lcd_Control_Write(0x32);
	Delay_ms(50);
	Lcd_Control_Write(0x28);
	Delay_ms(50);
	Lcd_Control_Write(0x01);
	Delay_ms(50);
	Lcd_Control_Write(0x06);
	Delay_ms(50);
	Lcd_Control_Write(0x0C);
	Delay_ms(50);
	Lcd_Control_Write(0x02);
	Delay_ms(50);
}



int main() {
	config();
	Lcd_init();
	lcd_send_string("Hoang Minh Nhan");
}


	



