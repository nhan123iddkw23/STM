/*
* File: lcd.c
* Author: Hoang Minh Nhan
* Date: 27/08/2023
* Description: Day la file c cua thu vien LCD
*/


#include <stm32f10x.h>
#include <delay.h>
#include <stdio.h>
#include <lcd.h>
#include <string.h>

/*
* Function: GPIO_LCD_Config
* Description: Ham cau hinh chan cho LCD
* Input:
*   none
* Output:
*   none
*/
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

/*
* Function: LCD_Enable
* Description: Ham bat man hinh LCD
* Input:
*   none
* Output:
*   none
*/
void LCD_Enable(void)
{
  GPIO_SetBits(GPIOC, LCD_EN);
  Delay_ms(2);
  GPIO_ResetBits(GPIOC, LCD_EN);
  Delay_ms(2);
}

/*
* Function: LCD_Send4Bit
* Description: Ham ghi data, ghi 4 bit
* Input:
*   char Data
* Output:
*   none
*/
void LCD_Send_4Bit(unsigned char Data)
{
   GPIO_WriteBit(GPIOA, LCD_D4, Data & 0x01);
   GPIO_WriteBit(GPIOA, LCD_D5, (Data>>1)&1);
   GPIO_WriteBit(GPIOA, LCD_D6, (Data>>2)&1);
   GPIO_WriteBit(GPIOA, LCD_D7, (Data>>3)&1);
}

/*
* Function: LCD_SendCommand
* Description: Ham ghi 4 bit ghi 2 lan
* Input:
*   char Command
* Output:
*   none
*/
void LCD_Send_Command(unsigned char command)
{
  LCD_Send_4Bit(command >> 4);
  LCD_Enable();
  LCD_Send_4Bit(command);
  LCD_Enable();
}

/*
* Function: LCD_Clear
* Description: Ham xoa LCD
* Input:
*   none
* Output:
*   none
*/
void LCD_Clear()
{
  LCD_Send_Command(0x01);
  Delay_ms(1);
}

/*
* Function: LCD_Init
* Description: Ham cau hinh cac thong so cho LCD
* Input:
*   none
* Output:
*   none
*/
void LCD_Init()
{
GPIO_LCD_Config();
LCD_Send_4Bit(0x00);
GPIO_WriteBit(GPIOC, LCD_RS, 0);
LCD_Send_4Bit(0x03);
LCD_Enable();
LCD_Enable();
LCD_Enable();
LCD_Send_4Bit(0x02);
LCD_Enable();
LCD_Send_Command(0x28); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
LCD_Send_Command(0x0C); // cho phep hien thi man hinh
LCD_Send_Command(0x06); // tang ID, khong dich khung hinh
LCD_Send_Command(0x01); // xoa toan bo khung hinh
}

/*
* Function: LCD_Gotoxy
* Description: Ham xac dinh vi tri ghi ki tu ra LCD
* Input:
*   char x
*   char y
* Output:
*   none
*/
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
unsigned char address;
if(y == 0) {
	address=(0x80+x);
  }
else if(y == 1) {
	 address=(0xc0+x);
  }
   LCD_Send_Command(address);
}

/*
* Function: LCD_PutChar
* Description: Ham ghi ki tu ra LCD
* Input:
*   char Data
* Output:
*   none
*/
void LCD_PutChar(unsigned char Data)
{
    GPIO_SetBits(GPIOC, LCD_RS);
    LCD_Send_Command(Data);
    GPIO_ResetBits(GPIOC, LCD_RS);
}

/*
* Function: LCD_Puts
* Description: Ham ghi mot chuoi ra LCD
* Input:
*   char *s
* Output:
*   none
*/
void LCD_Puts(char *s)
{
   while (*s)
    {
    LCD_PutChar(*s);
    s++;
    }
}
/*
* Function: LCD_Number
* Description: Ham ghi mot so ra LCD
* Input:
*   uint16_t number
* Output:
*   none
*/
void LCD_Number(char data[]) {
	 char *str;
		 sprintf(str,"%s",data);
		 LCD_Puts(str);
}

	 



