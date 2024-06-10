/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 2/06/2023
* Description: Day la file Dio.c
*/
#include <Dio.h>
#include <setjmp.h>

jmp_buf buf;

/*
* Function: config
* Description: Ham cau hinh GPIOB | GPIOC | GPIOA
* Input:
*   none
* Output:
*   none
*/
void config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  GPIO_InitTypeDef LED;
	  LED.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  LED.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOB, &LED);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	  GPIO_InitTypeDef LED1;
	  LED1.GPIO_Mode = GPIO_Mode_Out_PP;
	  LED1.GPIO_Pin = GPIO_Pin_13;
	  LED1.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC, &LED1);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  GPIO_InitTypeDef BUTTON;
	  BUTTON.GPIO_Mode = GPIO_Mode_IPU;
	  BUTTON.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  LED1.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOA, &BUTTON);
}

/*
* Function: Dio_WriteChannel
* Description: Day la ham xuat muc 1 hoac 0 ra chan STM32F10C8T6
* Input:
*    ChannelId  - Day la bien Dio_ChannelType(Kieu Enum)
*    Level      - Day la bien Dio_LevelType(Kieu Enum)
* Output:
*    none
*/
	void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
	  GPIO_TypeDef * gpioPort;
	  uint16_t gpioPin;
	  switch(ChannelId) {
			case DIO_CHANNEL_PB5:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_5;
			    break;
			case DIO_CHANNEL_PB6:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_6;
			    break;
			case DIO_CHANNEL_PB7:
				  gpioPort = GPIOB;
			    gpioPin  = GPIO_Pin_7;
			    break;
			case DIO_CHANNEL_PC13:
				  gpioPort = GPIOC;
			    gpioPin  = GPIO_Pin_13;
			    break;
			}
	  if(Level == STD_LOW) { 
			 GPIO_ResetBits(gpioPort,gpioPin);  // Xuat ra muc 0 tren chan STM32F103C8T6
			}
		else{
			GPIO_SetBits(gpioPort,gpioPin);     // Xuat ra muc 1 tren chan STM32F103C8T6
			}
		}

/*
* Function: Dio_ReadChannel
* Description: Day la ham doc muc 1 hoac 0 cua chan STM32F10C8T6
* Input:
*    ChannelId  - Day la bien Dio_ChannelType(Kieu Enum)
* Output:
*    STD_LOW  - Day la muc 0 
*    STD_HIGH - Day la muc 1
*/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId) {
	    GPIO_TypeDef * gpioPort;
	    uint16_t gpioPin;
	       switch(ChannelId) {
		          case DIO_CHANNEL_PC13:
				           gpioPort = GPIOC;
			             gpioPin = GPIO_Pin_13;
			              break;
		          case DIO_CHANNEL_PB5:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_5;
			              break;
							case DIO_CHANNEL_PB6:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_6;
			              break;
							case DIO_CHANNEL_PB7:
				            gpioPort = GPIOB;
			              gpioPin = GPIO_Pin_7;
			              break;
							 case DIO_CHANNEL_PA5:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_5;
			              break;
							case DIO_CHANNEL_PA6:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_6;
			              break;
							case DIO_CHANNEL_PA7:
				            gpioPort = GPIOA;
			              gpioPin = GPIO_Pin_7;
			              break;
		}
	if(GPIO_ReadInputDataBit(gpioPort,gpioPin)==0) { // Ham doc dau vao cua chan STM32F103C8T6 muc 1 hoac 0
		  return STD_LOW; // STD_LOW kieu enum
		}
	else {
		  return STD_HIGH;  // STD_HIGH kieu enum
		}
	}


/*
* Function: BlinkLED
* Description: Day la ham nhay tung led
* Input:
*    none
* Output:
*   none 
*   none
*/
void BlinkLED() {
	  uint8_t i;
	  for(i = 0; i < 6 ; i++) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
			delay();
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
			delay();
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1);
				}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				 longjmp(buf,2);
			  }
		}
}

/*
* Function: LED
* Description: Day la ham nhay 2 led va 1 led
* Input:
*    none
* Output:
*   none 
*   none
*/
void LED() {
	volatile uint8_t i;
	   for(i = 0;i<10;i++) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
			 delay();
			 	if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
			  longjmp(buf,0);
			}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				  longjmp(buf,2);
		    	}
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
			 delay();
			if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
			  longjmp(buf,0);
			}
			else if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW) {
				  longjmp(buf,2);
		    	}
			}
	}

/*
* Function: LED1
* Description: Day la ham nhay 3 led
* Input:
*    none
* Output:
*   none 
*   none
*/	
void LED1() {
	 while(1) {
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_HIGH);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_HIGH);
     delay();
	    if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
				  longjmp(buf,0);
			}
			if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1);
		  	}
			Dio_WriteChannel(DIO_CHANNEL_PB5,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB6,STD_LOW);
			Dio_WriteChannel(DIO_CHANNEL_PB7,STD_LOW);
     delay();
	    if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW) {
				  longjmp(buf,0);
			}
		  if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW) {
				  longjmp(buf,1); 
		  	}
	  }
}

/*
* Function: delay
* Description: Day la ham tao do tre
* Input:
*    none
* Output:
*   none 
*   none
*/
	void delay(){
		volatile uint32_t i;
		  for(i = 0;i < 1000000;i++);
}

/*
* Function: program
* Description: Day la ham su dung nut bam
* Input:
*    none
* Output:
*   none 
*   none
*/
void program() {
	  uint8_t i;
	  i = setjmp(buf);
	  while(1) {
			if(i == 0){
			 if(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW ){// doc muc logic tai chan PA5
				 while(Dio_ReadChannel(DIO_CHANNEL_PA5) == STD_LOW); // Cho nha nut bam
				    BlinkLED();
				}
			 }
			else if(i==1){
			  if(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW){// doc muc logic tai chan PA6
				 while(Dio_ReadChannel(DIO_CHANNEL_PA6) == STD_LOW); // Cho nha nut bam
				    LED();
					 }
				}
			else if(i == 2){
			   if(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW ){// doc muc logic tai chan PA7
				 while(Dio_ReadChannel(DIO_CHANNEL_PA7) == STD_LOW); // Cho nha nut bam
					  LED1();
					}
				 }
			}
		}