
void blink(){


	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	 HAL_Delay(100);

}

void blink2(){


	 GPIOA->BSRR = GPIO_PIN_5;  //ON
	 HAL_Delay(100);
	 GPIOA->BSRR = GPIO_PIN_5<<16; //OFF
	 HAL_Delay(100);

}

void but1(){


	  if(GPIOC->IDR & GPIO_PIN_13){
		  // HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)

		 // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		  GPIOA->BSRR = GPIO_PIN_5;
	  }else{

		//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		  GPIOA->BSRR = GPIO_PIN_5<<16;

	  }

}


void but2(){
	
	#include "stdbool.h"
	
	bool flag, flag_block1, flag_set1;
	
	flag = 1;
	flag_block1 = 0;
	flag_set1 = 0;


	 
	 if((GPIOC->IDR & GPIO_PIN_13)&& !flag_block1){

     		  flag_block1 = 1;
     		  flag_set1 = !flag_set1;

     		 if(flag_set1){

     			 //GPIOA->BSRR = GPIO_PIN_5; //ON
     			  GPIOA->BSRR = 0x0020; // 0b0000000000100000 ON

     		 }else if(!flag_set1){

     		   // GPIOA->BSRR = GPIO_PIN_5<<16;
     		    GPIOA->BSRR = 0x200000; // 0b0000 0000 0010 0000 << 16  = (0x200000) (0b1000000000000000000000) 0FF


     		 }

     	  }else if(!(GPIOC->IDR & GPIO_PIN_13)&& flag_block1){
     		  flag_block1 = 0;
     	  }
	
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{
		uint32_t error = HAL_UART_GetError(&huart2);

		if(error & HAL_UART_ERROR_PE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callbck - Parity error \n", 29);
			__HAL_UART_CLEAR_PEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_NE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callbck - Noise error \n", 28);
			__HAL_UART_CLEAR_NEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_FE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callbck - Frame error \n", 28);
			__HAL_UART_CLEAR_FEFLAG(&huart2);
		}

		if(error & HAL_UART_ERROR_ORE)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callbck - Overrun error \n", 28);
			__HAL_UART_CLEAR_OREFLAG(&huart2);

		}

		if(error & HAL_UART_ERROR_DMA)
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) "ERROR_Callbck - Overrun error \n", 28);
			__HAL_UART_CLEAR_NEFLAG(&huart2);
		}

		huart ->ErrorCode = HAL_UART_ERROR_NONE;


	}

};



