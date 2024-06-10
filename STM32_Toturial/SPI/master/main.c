/*
* File: SPI.c
* Author: Hoang Minh Nhan
* Date: 13/06/2023
* Description: Day la file code SPI
*/
#include <stm32f10x.h>
#include <delay.h>

void config();
void SPI_Soft_Init();
void Clock();
void SPI_Soft_Transmit(uint8_t data);
//void Check_Data();
uint8_t _data = 0x00;
int main() {
	 config();
	 while(1) {
	 SPI_Soft_Init();
	 SPI_Soft_Transmit(56); //0011 1000
	 //void Check_Data();
	 }
	}

/*
* Function: config
* Description: Ham cau hinh GPIOA
* Input:
*   none
* Output:
*   none
*/
void config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef SPI;
	SPI.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	SPI.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&SPI);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef BUTTON;
	BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	BUTTON.GPIO_Pin = GPIO_Pin_0;
	BUTTON.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&BUTTON);
}
/*
* Function: SPI_Soft_Init
* Description: Ham cau hinh SPI
* Input:
*   none
* Output:
*   none
*/
void SPI_Soft_Init() {
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0); // Chan CLK, dua ve muc 0
	  GPIO_ResetBits(GPIOA,GPIO_Pin_1); // Chan MOSI, dua ve muc 0
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);  // Chan SS, dua ve muc 1
	}
/*
* Function: Clock
* Description: Ham tao xung bang delay 1ms
* Input:
*   none
* Output:
*   none
*/
void Clock() {
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);
	  Delay_ms(5); // cho delay 1s de nhin thay led sang 
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	  Delay_ms(5);
	}

	/*
* Function: SPI_Soft_Transmit
* Description: Ham truyen du lieu
* Input:
*   uint8_t data: day la bien kieu uint8_t 
* Output:
*   none
*/
void SPI_Soft_Transmit(uint8_t data) {
		 while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 1);
		 if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0) {
			 uint8_t x = 0;
	   GPIO_ResetBits(GPIOA,GPIO_Pin_2); // Chan ss dua ve muc 0, bat dau truyen du lieu
	       for(uint8_t i = 0; i < 8; i++) {
			       if((data&0x80) == 0) { //day tu bit thap den bit cao
				          GPIO_ResetBits(GPIOA,GPIO_Pin_1);
							     x = 0;
				         }
			       else {
				           GPIO_SetBits(GPIOA,GPIO_Pin_1);
							     x = 1;
	           }
						 _data = _data<<1;
						 _data = _data|x; 
						 data = data<<1;
						 Clock();
         }
		   GPIO_SetBits(GPIOA,GPIO_Pin_2);
				  if(_data == 0x38) {
			 GPIO_SetBits(GPIOA,GPIO_Pin_3);
			 Delay_ms(500);
			 GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	     Delay_ms(500);
				 }
     }
}




