/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define FLASH_ADDR_PAGE_126 ((uint32_t)0x0801F810)	//Page 126
#define FLASH_ADDR_PAGE_127 ((uint32_t)0x0801FC00)	//Page 127

#define FLASH_USER_START_ADDR   FLASH_ADDR_PAGE_126
#define FLASH_USER_END_ADDR     FLASH_ADDR_PAGE_127 + FLASH_PAGE_SIZE
#define FLASH_ACR 0x00
#define FLASH_KEYR 0x04
#define FLASH_OPTKEYR 0x08
#define FLASH_SR 0x0C
#define FLASH_CR 0x10
#define FLASH_OPTCR 0x14
#define ADD ((uint32_t)0x0801FC01)
void Bumm_Flash();
uint32_t Address_Perius = 0;
uint32_t Data_1 = 0;
 uint32_t New_Address;
 struct {
	   volatile uint32_t Flash_New_Address;
	   volatile uint32_t Flash_This_Data;
	}C_EEPROM;
void FLASH_WritePage(uint32_t startPage, uint32_t endPage, uint32_t data);
uint32_t FLASH_ReadData(uint32_t addr);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void Write_flash(uint32_t address, uint32_t data);
void Flash_earse(uint32_t address);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Write_Data_to_Flash(uint32_t Address,uint32_t data);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t check = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
   FLASH_WritePage(FLASH_USER_START_ADDR,FLASH_USER_END_ADDR,0x5456);
//	 Write_Data_to_Flash(0x0801F820,0x2345);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//void Flash_earse(uint32_t address) {
//	HAL_FLASH_Unlock();
//	FLASH_EraseInitTypeDef flash;
//	flash.Banks = 1;
//	flash.NbPages = 1;
//	flash.PageAddress = address;
//	flash.TypeErase = FLASH_TYPEERASE_PAGES;
//	uint32_t pages;
//	HAL_FLASHEx_Erase(&flash,&pages);
//	HAL_FLASH_Lock();
//}

//void Write_flash(uint32_t address, uint32_t data) {
//	HAL_FLASH_Unlock();
//	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address,data);
//	HAL_FLASH_Lock();
//}

void FLASH_WritePage(uint32_t startPage, uint32_t endPage, uint32_t data)
{
	

  HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInit;
	EraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInit.PageAddress = startPage;
	EraseInit.NbPages = (endPage - startPage)/FLASH_PAGE_SIZE;
	uint32_t PageError = 0;
  Bumm_Flash();
	if(C_EEPROM.Flash_This_Data != 0xFFFFFFFF && C_EEPROM.Flash_New_Address < FLASH_ADDR_PAGE_127){
	   HAL_FLASHEx_Erase(&EraseInit, &PageError);
	}
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, C_EEPROM.Flash_New_Address, data);
  HAL_FLASH_Lock();
}
uint32_t FLASH_ReadData(uint32_t addr)
{
	uint32_t data = *(__IO uint32_t *)(addr);
	return data;
}

void Bumm_Flash() {
	   for(uint32_t i = FLASH_ADDR_PAGE_126; i < FLASH_ADDR_PAGE_127; i+=4) {
			  C_EEPROM.Flash_This_Data = FLASH_ReadData(i);
			  if( C_EEPROM.Flash_This_Data  == 0xFFFFFFFF) {
					 C_EEPROM.Flash_New_Address = i;
					 break;
					}
			 }
}

	
void Write_Data_to_Flash(uint32_t Address,uint32_t data) {
	 if((FLASH->CR &(1 << 7)) !=0) {   // check key and unlock. 1 LOCK, 0 UNLOCK
		  FLASH->KEYR = 0x45670123;
		  FLASH->KEYR = 0xCDEF89AB;
		 check = 1;
		 }
	 	while((FLASH->SR & (1 << 0)) == 1);  // flag busy  : 1 = busy 0 = not busy 
		check = 3;
	    FLASH->CR |= (1 << 0); // write data
		  *(uint32_t*)Address = data;
		 check = 4;		 
	//	 while((FLASH->SR & (1<<0)) == 1); // flag busy  : 1 = busy 0 = not busy 
		  check = 6;
		  FLASH->CR &= (0 << 0);
			 check = 7;
		  FLASH->CR &= (0 << 7);
		 
	  }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
