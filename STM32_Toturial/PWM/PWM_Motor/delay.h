/*
* File: delay.h
* Author: Hoang Minh Nhan
* Date: 6/06/2023
* Description: Day la file .h
*/
#ifndef __DELAY_H
#define __DELAY_H
#include <stm32f10x.h>
void Init_TIMER();
void Delay_1ms();
void Delay_ms(unsigned int time_ms);


#endif