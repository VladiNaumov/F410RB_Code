/* USER CODE BEGIN Header */
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

#include "main.h"

uint8_t rx_buff[5]; // буфер (массив) на прием данных
uint8_t tx_buff[]={1,2,3,4,5}; // буфер (массив) на передачу данных
uint8_t str[] = "HELLO-UART\r\n\0";

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
 
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();


  HAL_UART_Transmit(&huart1, str, 12, 1000); // передачу данных

  HAL_UART_Transmit_IT(&huart1, tx_buff, 5); //передача данных
  HAL_UARTEx_ReceiveToIdle_IT(&huart1, rx_buff, 5);  // прием данных с компьютера

  /* to While() */

  /*
      HAL_UART_Transmit(&huart1, str, 12, 3000); // передачу данных
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
   */

  while (1)
  {
    /* USER CODE */
  }
  
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{


  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
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
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	__NOP();

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	__NOP();

}


/*

void HAL_UARTEx_RxEventCallback (UART_HandleTypeDef *huart, uint16_t Size)
{

	{
		HAL_UART_Transmit_IT(&huart1, tx_buff, 5); //передача данных
		HAL_UARTEx_ReceiveToIdle_IT(&huart1, rx_buff, 5);  // прием данных с компьютера
	}
}
*/


/*
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{
		uint32_t error = HAL_UART_GetError(&huart2);

		if(error & HAL_UART_ERROR_PE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callback - Parity error \n", 29);
			__HAL_UART_CLEAR_PEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_NE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callback - Noise error \n", 28);
			__HAL_UART_CLEAR_NEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_FE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callback - Frame error \n", 28);
			__HAL_UART_CLEAR_FEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_ORE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callback - Overrun error \n", 28);
			__HAL_UART_CLEAR_OREFLAG(&huart2);

		}

		if(error & HAL_UART_ERROR_DMA)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callback - Overrun error \n", 28);
			__HAL_UART_CLEAR_NEFLAG(&huart2);
		}

		huart ->ErrorCode = HAL_UART_ERROR_NONE;


	}

};

*/


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

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

}
#endif /* USE_FULL_ASSERT */
