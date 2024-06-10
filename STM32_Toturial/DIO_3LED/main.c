/*
* File: main.c
* Author: Hoang Minh Nhan
* Date: 2/06/2023
* Description: Day la file main.c
*/
#include <stm32f10x.h>
#include <Dio.h>

int main(void) {
	  config(); // Ham cau hinh GPIO
	  program(); // Ham nhay led su dung setjum
	}
			
