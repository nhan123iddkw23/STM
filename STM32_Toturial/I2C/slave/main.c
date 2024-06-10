#include <stm32f10x.h>
#include <stdbool.h>
#include <delay.h>


#define SCL GPIO_Pin_1
#define SDA GPIO_Pin_2

uint8_t address = 0x32;
uint8_t data = 0x00;
bool Rw;
bool check = 0;
uint8_t ADDRESS = 0x00;
void config();
void SDA_INPUT();
void SDA_OUTPUT();
void Read_Address();
bool Read_Write();
void Check_Address();
void Read_data();
uint8_t ACK_NACK();
uint8_t a = 0;

int main() {

	   }
	

void config() {
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitTypeDef CLOCK;
	 CLOCK.GPIO_Mode =GPIO_Mode_AF_OD;
	 CLOCK.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	 CLOCK.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&CLOCK);
}



void Read_Address() {
	 uint8_t x = 0;
	  while(x<7) { 
			 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1) { // doc clk
				 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
				 check = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);  // doc data
				 ADDRESS = (ADDRESS << x) | check;
				 x++;
			}
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
		}
		 Rw = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
	}



void Check_Address() {
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1); // cho clk
				  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0) {
	if(address != ADDRESS) {
		 GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else {
		 GPIO_SetBits(GPIOA,GPIO_Pin_2);
	      }
     }
	}	

uint8_t ACK_NACK() {
	   if(data != 0) {
			 return 0;
		 }
		 else {
			 return 1;
		 }
	 }


	
	  

	
	  
