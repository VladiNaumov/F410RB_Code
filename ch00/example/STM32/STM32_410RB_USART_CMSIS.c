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
#include "usart.h"
#include "gpio.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/

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
  
  /* USER CODE BEGIN 2 */
  
/*--------  определение констант --------------------*/
  #define MY_UART USART2


 /* ------ Sending  message --------------*/

   void UarSendChar(char ch) // пример interrupts (прерывание) по опросу
   {
	   /* USART2->SR: Это ссылка на регистр состояния USART1, где хранятся различные флаги состояния */
	   /* USART_SR_TC - это флаг (Transmission Complete), который указывает на то, что передача данных через USART завершена */

	   while ((MY_UART->SR & USART_SR_TC) == 0){}

	  
  /* передать байт данных */
	  MY_UART->DR = ch;
	  
   }
   
   void UsarSendString(const char* txt)
   {
	   while (*txt != 0)
	   {
		   UarSendChar (*txt++);
	   }
   }
   
   /* ------ geting massage --------------*/
   
   char UsartGetChar(void)  // пример interrupts (прерывание) по опросу
   {
	   /* USART2->SR: Это ссылка на регистр состояния USART1, где хранятся различные флаги состояния */
	   /* USART_SR_RXNE: Это константа флага, обозначающая, что входной буфер данных USART не пуст. */
	   
	   while ((MY_UART->SR & USART_SR_RXNE) == 0){}
	   
	   return MY_UART->DR;
   }
   
   int UsarGetString (char* txt, int maxLen)
   {
	   int pos = 0;
	   while (pos < maxLen -1)
	   {
		   txt[pos] = UsartGetChar();
		   if(txt[pos] < ' ')
		   {
			   txt[pos++] = 0;
			   return pos;
		   }
		   pos +=1;
	   }
	   txt [pos++] = 0;
	   return pos;
   }

 UarSendChar('A');
 UarSendChar('B');
 UarSendChar('C');
 UarSendChar('\n');

 UsarSendString("HELLO IM BOOOT \r\n ");


  /* USER CODE END 2 */

  while (1)
  {

	char txt [100];
	UsarGetString(txt, sizeof(txt));
	UsarSendString(txt);
	UsarSendString("\r\n");

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
