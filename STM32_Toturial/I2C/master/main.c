#include <stm32f10x.h>
#include <delay.h>
#include <stdbool.h>

#define SCL GPIO_Pin_1
#define SDA GPIO_Pin_2

static void I2C_Data(uint8_t data);
static void I2C_Start();
static void I2C_Stop();
static bool I2C_ReadorWrite(bool check);
static void Clock();
static void I2C_Address(uint8_t address,bool check);
static bool  ACK_NACK();
static void config();
bool Rw;


int main() {
	while(1){

	}
}
	
	
void config() {
	 // config cac chan I2C
	 GPIO_InitTypeDef I2C;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 I2C.GPIO_Mode = GPIO_Mode_AF_OD;
	 I2C.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	 I2C.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&I2C);
	 // Config button
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_InitTypeDef BUTTON;
	 BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	 BUTTON.GPIO_Pin = GPIO_Pin_0;
	 I2C.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&BUTTON);
}


static void I2C_Start(){
	GPIO_SetBits(GPIOA,SDA);
	GPIO_SetBits(GPIOA,SCL);
	while(GPIO_ReadInputDataBit(GPIOA,SCL) == 1) {
		 GPIO_ResetBits(GPIOA,SDA);
		 GPIO_ResetBits(GPIOA,SCL);
		 
	}
}

static void Clock(){
	 GPIO_SetBits(GPIOA,SCL);
	 Delay_1ms();
	 GPIO_ResetBits(GPIOA,SCL);
	 Delay_1ms();
}


static bool I2C_ReadorWrite(bool check){
	 if(check == 1) {
		 return 1;
	 }
	 return 0;
}

static void I2C_Address(uint8_t address,bool check){
	 uint8_t data_address[8];
	     data_address[0] = I2C_ReadorWrite(check);
	     Clock();
	   for(uint8_t i = 0; i < 8; i++) {
	     data_address[i+1]  = (address>>i)&1;
			 Clock();
		 }
		 
}
