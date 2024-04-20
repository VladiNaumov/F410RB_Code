/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/*
порядок инициализации STM32F410RB

1. Запуск отладчика SYS (Serial Wire, SWO)
2. Запуск тактирования RCC (Crystal ceramic resonator)
2. Инициализация портов (GPIOA, GPIOB, GPIOC, GPIOH)

*/

#include "main.h"
#include "usart.h"
#include "gpio.h"

// System Clock Configuration
void SystemClock_Config(void);

//  GPIO Initialization Function
static void MX_GPIO_Init(void);

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();


  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  while (1)
  {
    /* USER CODE END WHILE */
	  
	 //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	 //GPIOA->BSRR = GPIO_PIN_5; //ON
     GPIOA->BSRR = 0x0020; //  ON
	 HAL_Delay(100);
	 //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	 //GPIOA->BSRR = GPIO_PIN_5<<16;
     GPIOA->BSRR = 0x200000; // OFF
	 HAL_Delay(100);
	  
    /* USER CODE BEGIN 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

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
