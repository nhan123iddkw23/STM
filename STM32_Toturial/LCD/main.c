#include <stm32f10x.h>
#include <delay.h>
#include <lcd.h>

int main(void)
{
	uint8_t data[6] = {0,1,2,4,5,6};
LCD_Init();
//while(1) {
LCD_Gotoxy(0,0);
LCD_Puts("Download");
LCD_Gotoxy(0,1);
//LCD_Puts("Upload");

//LCD_Send_Command(0x18);
//Delay_ms(300);
  }
//}

