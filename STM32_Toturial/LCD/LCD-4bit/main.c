#include <stm32f10x.h>
#include <delay.h>
#include <stdio.h>


#define LCD_RS GPIO_Pin_13
#define LCD_RW GPIO_Pin_14
#define LCD_EN GPIO_Pin_15
#define LCD_D4 GPIO_Pin_0
#define LCD_D5 GPIO_Pin_1
#define LCD_D6 GPIO_Pin_2
#define LCD_D7 GPIO_Pin_3


void GPIO_LCD_Config(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitTypeDef GPIO_LCD_InitStruction;
/*Configure GPIO pin Output Level */
GPIO_WriteBit(GPIOA, LCD_D4|LCD_D5|LCD_D5|LCD_D7, 0);
GPIO_WriteBit(GPIOC, LCD_RS|LCD_RW|LCD_EN, 0);
GPIO_LCD_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_LCD_InitStruction.GPIO_Pin = LCD_D4|LCD_D5|LCD_D6|LCD_D7;
GPIO_LCD_InitStruction.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_Init(GPIOA, &GPIO_LCD_InitStruction);
GPIO_LCD_InitStruction.GPIO_Pin = LCD_EN|LCD_RS|LCD_RW;
GPIO_Init(GPIOC, &GPIO_LCD_InitStruction);
}


void LCD_Write_Command(char Data)
{
     GPIO_WriteBit(GPIOC, LCD_RS,Bit_RESET);
     GPIO_WriteBit(GPIOA, LCD_D4, (Data>>4)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D5, (Data>>5)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D6, (Data>>6)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D7, (Data>>7)&0x01);
     GPIO_SetBits(GPIOC,LCD_EN);
     Delay_ms(5);
     GPIO_ResetBits(GPIOC,LCD_EN);
     GPIO_WriteBit(GPIOC, LCD_RS,Bit_RESET);
     GPIO_WriteBit(GPIOA, LCD_D4, (Data>>0)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D5, (Data>>1)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D6, (Data>>2)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D7, (Data>>3)&0x01);
     GPIO_SetBits(GPIOC,LCD_EN);
     Delay_ms(5);
     GPIO_ResetBits(GPIOC,LCD_EN);
}

void LCD_Write_Data(char Data)
{    GPIO_WriteBit(GPIOC, LCD_RS,Bit_SET);
     GPIO_WriteBit(GPIOA, LCD_D4, (Data>>4)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D5, (Data>>5)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D6, (Data>>6)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D7, (Data>>7)&0x01);
     GPIO_SetBits(GPIOC,LCD_EN);
     Delay_ms(5);
     GPIO_ResetBits(GPIOC,LCD_EN);
     GPIO_WriteBit(GPIOC, LCD_RS,Bit_SET);
     GPIO_WriteBit(GPIOA, LCD_D4, (Data>>0)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D5, (Data>>1)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D6, (Data>>2)&0x01);
     GPIO_WriteBit(GPIOA, LCD_D7, (Data>>3)&0x01);
     GPIO_SetBits(GPIOC,LCD_EN);
     Delay_ms(5);
     GPIO_ResetBits(GPIOC,LCD_EN);
}
 
void LCD_Init()
{
GPIO_LCD_Config(); 
LCD_Write_Command(0x28); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
Delay_ms(1);
LCD_Write_Command(0x0C); // cho phep hien thi man hinh
Delay_ms(1);
LCD_Write_Command(0x06); // tang ID, khong dich khung hinh
Delay_ms(1);
LCD_Write_Command(0x01); // xoa toan bo khung hinh
}
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
unsigned char address;
if(y == 0)address=(0x80+x);
else if(y == 1) address=(0xC0+x);
LCD_Write_Command(address);
}

void LCD_Puts(char *s)
{
while (*s)
{
LCD_Write_Data(*s);
s++;
}
}

void LCD_Number(uint16_t number) {
	 char *str;
		 sprintf(str,"%d",number);
		 LCD_Puts(str);
}

void LCD_Number_Array(uint8_t Array[],uint8_t len) {
	char str[len];
	 for(int i = 0; i < len; i++) {
		 str[i] = (0x30+Array[i]) ;
	 }
	   LCD_Puts(str);
 }
uint8_t Array[8] = {1,7,0,6,2,0,0,3};
int main() {
	 LCD_Init();
	// while(1) {
	 LCD_Gotoxy(0,0);
	 //LCD_Puts("Hoang Minh Nhan");
		LCD_Number(2476);
	 LCD_Gotoxy(0,1);
	 //LCD_Puts("Toi se giup em vuot qua ho sau tieu cuc nay");
	 //LCD_Write_Data('B');
	 //LCD_Write_Command(0x18);
	 //Delay_ms(200);
	 //}
	  LCD_Number_Array(Array,8);
}