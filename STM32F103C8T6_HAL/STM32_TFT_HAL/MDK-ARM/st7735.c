
#include "st7735.h"
SPI_HandleTypeDef *spi;




void SPI_WriteByte(uint8_t data)
{
  while(!(SPI2->SR & SPI_SR_TXE));
  SPI2->DR = data;
}


void ST7735_sendCommand(uint8_t cmd)
{
  while(!(SPI2->SR & SPI_SR_TXE));
  while(SPI2->SR & SPI_SR_BSY);
	
  A0_LOW;
  SPI2->DR = cmd;
	
  while(!(SPI2->SR & SPI_SR_TXE));
  while(SPI2->SR & SPI_SR_BSY);
  
  A0_HIGH;
}

void ST7735_SetWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  ST7735_sendCommand(0x2A);
  SPI_WriteByte(0x00);
  SPI_WriteByte(x + 0);
  SPI_WriteByte(0x00);
  SPI_WriteByte((x + w));

  ST7735_sendCommand(0x2B);
  SPI_WriteByte(0x00);
  SPI_WriteByte(y + 0);
  SPI_WriteByte(0x00);
  SPI_WriteByte((y + h) + 0);

  ST7735_sendCommand(0x2C);
}
void ST7735_Clr(void)
{
  ST7735_SetWindow(0, 0, 160, 128);
  for(unsigned int i = 0; i < (160 * (128)); i++)
	{
    SPI_WriteByte(0);
    SPI_WriteByte(0);
  }
}


void ST7735_init(SPI_HandleTypeDef *__spi)
{
	spi = __spi;
	
	spi->Instance->CR1 |= SPI_CR1_SPE;
	
	CS_LOW;
	
  ST7735_sendCommand(0x01); //Software Reset
  HAL_Delay(5);
  ST7735_sendCommand(0x11); //exit  Sleep
  HAL_Delay(5);
  
  
  ST7735_sendCommand(0xB1);  //Frame Rate Control (In normal mode/ Full colors)
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x2D);
  
  
  ST7735_sendCommand(0xB2);  //Frame Rate Control (In Idle mode/ 8-colors)
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x2D);
  
  
  ST7735_sendCommand(0xB3);  //Frame Rate Control (In Partial mode/ full colors)
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x2D);
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x2D);
  
  
  ST7735_sendCommand(0xB4);  //Display Inversion Control
  SPI_WriteByte(0x07);
  
  
  ST7735_sendCommand(0xC0);  //Power Control 1
  SPI_WriteByte(0xA2);
  SPI_WriteByte(0x02);
  SPI_WriteByte(0x84);
  
   
  ST7735_sendCommand(0xC1); //Power Control 2
  SPI_WriteByte(0xC5);
  
  
  ST7735_sendCommand(0xC2);  //Power Control 3 (in Normal mode/ Full colors)
  SPI_WriteByte(0x0A);
  SPI_WriteByte(0x00);
  
  
  ST7735_sendCommand(0xC3);  //Power Control 4 (in Idle mode/ 8-colors)
  SPI_WriteByte(0x8A);
  SPI_WriteByte(0x2A);
  
  
  ST7735_sendCommand(0xC4);  //Power Control 5 (in Partial mode/ full-colors)
  SPI_WriteByte(0x8A);
  SPI_WriteByte(0xEE);
  
  
  ST7735_sendCommand(0xC5);  //VCOM Control 1
  SPI_WriteByte(0x0E);
  
  
  ST7735_sendCommand(0x20);  //Display Inversion Off
  
  
  ST7735_sendCommand(0x36);  //Memory Data Access Control           
  SPI_WriteByte(0xA0); //RGB mode + che do man hinh ngang
  
  
  ST7735_sendCommand(0x3A); //Interface Pixel Format
  SPI_WriteByte(0x05); //16-bit/pixel
   
 
  ST7735_sendCommand(0x2A); //Column address set
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(160);
  
  
  ST7735_sendCommand(0x2B); //Row address set
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(128);
  
 
  ST7735_sendCommand(0xE0); //Gamm adjustment (+ polarity)
  SPI_WriteByte(0x02);
  SPI_WriteByte(0x1C);
  SPI_WriteByte(0x07);
  SPI_WriteByte(0x12);
  SPI_WriteByte(0x37);
  SPI_WriteByte(0x32);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x2D);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x25);
  SPI_WriteByte(0x2B);
  SPI_WriteByte(0x39);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x03);
  SPI_WriteByte(0x10);
  
  
  ST7735_sendCommand(0xE1);  //Gamma adjustment(- polarity)
  SPI_WriteByte(0x03);
  SPI_WriteByte(0x1D);
  SPI_WriteByte(0x07);
  SPI_WriteByte(0x06);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x2D);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x37);
  SPI_WriteByte(0x3F);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x02);
  SPI_WriteByte(0x10);
  
  ST7735_sendCommand(0x13); //Partial off (Normal)
  
  ST7735_sendCommand(0x29); //Display on
}

void ST7735_draw(uint16_t color)
{
	SPI_WriteByte(color>>8);
  SPI_WriteByte(color);
}

void ST7735_drawPixel(int16_t x,int16_t y,uint16_t color)
{
	if(x<0)return;
	if(y<0)return;
	if(x>=DEVICER_MAX_W)return;
	if(y>=DEVICER_MAX_H)return;
	ST7735_SetWindow(x,y,1,1);
	ST7735_draw(color);
}