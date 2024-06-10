/*
* File: lcd.h
* Author: Hoang Minh Nhan
* Date: 27/08/2023
* Description: Day la file h cua thu vien LCD
*/

#ifndef __LCD_H
#define __LCD_H
#include <stm32f10x.h>

#define LCD_RS GPIO_Pin_13 // Chan RS
#define LCD_RW GPIO_Pin_14 // Chan RW
#define LCD_EN GPIO_Pin_15 // Chan E
#define LCD_D4 GPIO_Pin_0  // Chan D4
#define LCD_D5 GPIO_Pin_1  // Chan D5
#define LCD_D6 GPIO_Pin_2  // Chan D6
#define LCD_D7 GPIO_Pin_3  // Chan D7

void GPIO_LCD_Config(void);   
void LCD_Enable(void);
void LCD_Send_4Bit(unsigned char Data);
void LCD_Send_Command(unsigned char command);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);
void LCD_Number(char data[]);
void LCD_Number_Array(uint8_t Array[],uint8_t len);


#endif