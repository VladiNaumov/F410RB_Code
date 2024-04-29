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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/*  STM32 — Bit Banding  */
#include "binBanding.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN  */
#define MY_UART USART2

/*-------- реализация кольцевого буфера ---------*/

  char bufToUART[128];
  char bufFromUart[128];

  typedef struct{
	  uint32_t wrPtr;
	  uint32_t rdPtr;
	  uint32_t size;
	  char* ptr;
  }RingBuftruct;

  RingBuftruct ringToUart = {0, 0, sizeof(bufToUART), bufToUART};
  RingBuftruct ringFromUart = {0, 0, sizeof(bufFromUart), bufFromUart};
  
  uint32_t rxCnt = 0;
  uint32_t rxserv = 0;

  int RingGetLen(RingBuftruct* ring)
  {
	  return ring->wrPtr - ring->rdPtr;
  }

  void RingInsert(RingBuftruct*  ring, char ch)
  {
	  if(RingGetLen(ring) >= ring->size)
	  {
		  return;
	  }

	 ring-> ptr [(ring->wrPtr++)%ring->size] = ch;
  }

  char RingGet(RingBuftruct* ring)
  {
	  if(RingGetLen(ring)==0)
	  {
		  return 0;
	  }
	 return ring->ptr [(ring->rdPtr++)%ring->size];

  }

   void UsarSendString(const char* txt)
   {
	   while (*txt != 0)
	   {
		  RingInsert(&ringToUart, *txt++);
	   }

	    BIT_BAND_PER(MY_UART->CR1, USART_CR1_TCIE) = 1;
   }
   
/*-------- UART/USART Global interrupt ---------*/
  void USART2_IRQHandler()
  {
	/* USART2->SR: Это Status Register  */
 	/* USART_SR_RXNE: Это константа флага, обозначающая, что входной буфер данных USART не пуст. */
 	 if (MY_UART->SR & USART_SR_RXNE) // Это означает, что в регистре находятся данные, которые можно прочитать
 	 {
		 // USART2 ->DR предназначен для записи данных, которые будут передаваться или приниматься через модуль USART
 		 char ch = MY_UART->DR;
 		 RingInsert (&ringFromUart, ch);
 		 if(ch == '\r')
 		 {
 			 rxCnt +=1;
 		 }
 	 }

 	/* USART2->SR: Это Status Register  */
 	
 	 if(MY_UART->SR & USART_SR_TC) /* USART_SR_TC - это флаг указывает на то, что передача данных через USART завершена */
 	 {
 		 if(RingGetLen(&ringToUart) == 0)
 		 {
			 //USART_CR1_TCIE определяет разрешение прерывания по завершению передачи данных.(TCIE = 1), то прерывание будет OFF после завершения передачи данных.
 			BIT_BAND_PER(MY_UART->CR1, USART_CR1_TCIE) = 0; // USART_CR1_TXEIE_TXNIE
 		 }else
 		 {
			 // USART2 ->DR предназначен для записи данных, которые будут передаваться или приниматься через модуль USART
 			 MY_UART->DR = RingGet(&ringToUart);
 		 }
 	 }
	 
	 /* Передача управления библиотечной функции HAL для обработки прерывания  */ 
	   HAL_UART_IRQHandler(&huart2); 

   }

   void UsarSendString(const char* txt)
   {
	   while (*txt != 0)
	   {
		  RingInsert(&ringToUart, *txt++);
	   }
	   //USART_CR1_TCIE определяет разрешение прерывания по завершению передачи данных.(TCIE = 1), то прерывание будет генерироваться после завершения передачи данных.
	   BIT_BAND_PER(MY_UART->CR1, USART_CR1_TCIE) = 1; //USART_CR1_TCIE
   }

/* USER CODE END */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  
 /* USER CODE  */
 
 /* UART/USART installation Global interrupt */
  //NVIC_EnabledRQ (USART2_IRQn);
  
  // Разрешить прерывания от USART2
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  //HAL_UART_IRQHandler(&huart2);
 
 
 UsarSendString("HELLO IM BOOOT \r\n ");
 
  /* USER CODE END */

  while (1)
  {

	/* USER CODE END WHILE */
		if(rxCnt != rxserv)
		{
			char ch;
		    int maxLen = RingGetLen(&ringFromUart);
			do{
				ch = RingGet(&ringFromUart);
				RingInsert(&ringToUart, ch);
			}while ((maxLen-- !=0 && ch!='\r'));
			RingInsert(&ringToUart,'\r');
			RingInsert(&ringToUart,'\n');
			
			BIT_BAND_PER(MY_UART->CR1, USART_CR1_TCIE) = 1;
			rxserv +=1;
			HAL_Delay(1000);
		}

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