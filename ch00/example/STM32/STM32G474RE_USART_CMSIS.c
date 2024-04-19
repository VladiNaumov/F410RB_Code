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


  /* USER CODE BEGIN */
  
  /*--------  STM32G474RE --------------------*/
  
  
  
    /*--------  определение констант --------------------*/
   #define MY_UART USART3
   #define TX_PORT GPIOC
   #define TX_PIN 10
   #define RX_PORT GPIOC
   #define RX_PIN 11


   /*--------  настройка GPIO --------------------*/

   /* установка тактирование GPIO*/
   RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN
   /* установка тактирование USART*/
   RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN

   /* Регистр MODER используется для установки режима работы каждого пина GPIO */
   TX_PORT->MODER &= ~(3<<(2*TX_PIN));
   TX_PORT->MODER |=  (2<<(2*TX_PIN));

   /*Регистр OSPEEDR используется для установки скорости выходных сигналов на пинах GPIO.*/
   TX_PORT->OSPEEDR &= ~(3<<(2*TX_PIN));
   TX_PORT->OSPEEDR |= (3<<(2*TX_PIN));

   if(TX_PIN >=8)
   {
 	  /*  Этот регистр используется для выбора альтернативной функции, которая будет назначена определенному пину GPIO */
 	  TX_PORT->AFR [1] &= ~(0x0f << (4 * (TX_PIN-8)));
 	  TX_PORT->AFR [1] |=  (0x07 << (4 * (TX_PIN-8)));
   }else
   {
 	  /*  Этот регистр используется для выбора альтернативной функции, которая будет назначена определенному пину GPIO */
 	  TX_PORT->AFR [0] &= ~(0x0f << (4 * (TX_PIN)));
 	  TX_PORT->AFR [0] |=  (0x07 << (4 * (TX_PIN)));

   }

   /* Регистр MODER используется для установки режима работы каждого пина GPIO */
   RX_PORT->MODER &= ~(3 << (2*RX_PIN));
   RX_PORT->MODER |=  (2 << (2*RX_PIN));

   if(RX_PIN >=8)
    {
  	  /*  Этот регистр используется для выбора альтернативной функции, которая будет назначена определенному пину GPIO */
 	  RX_PORT->AFR [1] &= ~(0x0f << (4 * (RX_PIN-8)));
 	  RX_PORT->AFR [1] |=  (0x07 << (4 * (RX_PIN-8)));
    }else
    {
  	  /*  Этот регистр используется для выбора альтернативной функции, которая будет назначена определенному пину GPIO */
 	   RX_PORT->AFR [0] &= ~(0x0f << (4 * (RX_PIN-8)));
 	   RX_PORT->AFR [0] |=  (0x07 << (4 * (RX_PIN-8)));

    }


   /* ------ настройка USART/UART --------------*/

   /* USART OFF */
   MY_UART->CR1 &= USART_CR1_UE;

   MY_UART->CR1 = USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_RE;
   MY_UART->CR2 = 0;
   MY_UART->CR3 = USART_CR3_OVRDIS;

   /* SPEED USART */
   MY_UART->BRR = 184;

   /* USART ON */
   MY_UART->CR1 |= USART_CR1_UE;

 /* ------ luetaan --------------*/

   void UarSendChar(char ch)
   {
 	  while ((MY_UART ->ISR & USART_ISR_RXNE_RXFNE)==0)
 	  {
 		  // inptu
 	  }

 	  MY_UART->TDR = ch;
   }

   UarSendChar('A');
   UarSendChar('B');
   UarSendChar('C');

  

  /* USER CODE END */
  
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
 
}
