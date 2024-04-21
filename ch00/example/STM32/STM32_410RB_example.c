
void blink()
{
     //HAL USE
         //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
         //HAL_Delay(100);
         //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
         //HAL_Delay(100);

     //CMSIS USE
        //GPIOA->BSRR = GPIO_PIN_5;  //ON
        //HAL_Delay(100);
        //GPIOA->BSRR = GPIO_PIN_5<<16; //OFF
        //HAL_Delay(100);

     //CMSIS USE
      GPIOA->BSRR = 0x0020; //ON
      HAL_Delay(100);
      GPIOA->BSRR = 0x200000; //OFF
      HAL_Delay(100);
}

void but1()
{
	  if(GPIOC->IDR & GPIO_PIN_13)
	  {
		 // HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
		 // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		  GPIOA->BSRR = GPIO_PIN_5;
	  }
	  else
	  {
		//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		  GPIOA->BSRR = GPIO_PIN_5<<16;
	  }
}

void but2()
{
	#include "stdbool.h"
	
	bool flag, flag_block1, flag_set1;
	
	flag = 1;
	flag_block1 = 0;
	flag_set1 = 0;

	 if((GPIOC->IDR & GPIO_PIN_13)&& !flag_block1)
	 {
     		  flag_block1 = 1;
     		  flag_set1 = !flag_set1;

     		 if(flag_set1)
     		 {
     			 //GPIOA->BSRR = GPIO_PIN_5; //ON
     			  GPIOA->BSRR = 0x0020; // 0b0000000000100000 ON
     		 }
     		 else if(!flag_set1)
     		 {
     		   //GPIOA->BSRR = GPIO_PIN_5<<16;
     		    GPIOA->BSRR = 0x200000; // 0b0000 0000 0010 0000 << 16  = (0x200000) (0b1000000000000000000000) 0FF
     		 }
     		 else if(!(GPIOC->IDR & GPIO_PIN_13)&& flag_block1)
     		 {
     		  flag_block1 = 0;
     	     }
    }

/*   UART   */

void HAL_UARTEx_RxEventCallback (UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{
		HAL_UART_Transmit_IT(&huart2, RxData, Size); //передача данных
		HAL_UARTEx_ReceiveToIdle_IT(&huart2, RxData, 5);  // прием данных с компьютера
	}
}


// фунция Callback
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

	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

/* UART&USART*/
uint8_t rx_buff[10]; // буфер (массив) на прием данных
uint8_t tx_buff[]={0,1,2,3,4,5,6,7,8,9}; // буфер (массив) на передачу данных

  void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
  HAL_UART_Receive_IT(&huart1, rx_buff, 10); // прием данных
  HAL_UART_Transmit_IT(&huart1, tx_buff, 10); // передачу данных


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	__NOP();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	__NOP();
}

 // сканирование I2C порта на наличие подключения 
void I2C_Scan ()
{
	// создание переменной, содержащей статус
        HAL_StatusTypeDef res;
	// сообщение о начале процедуры
        char info[] = "Scanning I2C bus...\r\n";
        // отправка сообщения по UART
        HAL_UART_Transmit(&huart2, (uint8_t*)info, strlen(info), HAL_MAX_DELAY);

	/* &huart5 - адрес используемого UART
	 * (uint8_t*)info - указатель на значение для отправки
	 * strlen(info) - длина отправляемого сообщения
	 * HAL_MAX_DELAY - задержка
	 */
	 
        // перебор всех возможных адресов
	for(uint16_t i = 0; i < 128; i++)
	{
            // проверяем, готово ли устройство по адресу i для связи
            res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, HAL_MAX_DELAY);
	    // если да, то
            if(res == HAL_OK)
	    {
	    	char msg[64];
	    	// запись адреса i, на который откликнулись, в строку в виде
                // 16тиричного значения:
	    	snprintf(msg, sizeof(msg), "0x%02X", i);
	    	// отправка номера откликнувшегося адреса
	    	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	    	// переход на новую строчку
	    	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
	    }
	    else HAL_UART_Transmit(&huart2, (uint8_t*)".", 1, HAL_MAX_DELAY);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
}

