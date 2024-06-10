
#ifndef __ST7735_H__
#define __ST7735_H__
#include "main.h"
#define DEVICER_MAX_W 160
#define DEVICER_MAX_H 128
 
#define WHITE             0xFFFF
#define BLACK             0x0000      
#define BLUE              0x001F  
#define RED               0xF800
#define MAGENTA           0xF81F
#define GREEN             0x07E0
#define CYAN              0x7FFF
#define YELLOW            0xFFE0
#define BROWN 		  0XBC40 
#define GRAY  		  0X8430
#define A0_LOW  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0)
#define A0_HIGH HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1)
#define CS_LOW  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0)
#define CS_HIGH HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1)
void ST7735_init(SPI_HandleTypeDef *__spi); 
void SPI_WriteByte(uint8_t data);
void ST7735_sendCommand(uint8_t cmd);
void ST7735_init(SPI_HandleTypeDef *__spi);
void ST7735_Clr(void);
void ST7735_SetWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void ST7735_draw(uint16_t color);
void ST7735_drawPixel(int16_t x,int16_t y,uint16_t color);
#endif