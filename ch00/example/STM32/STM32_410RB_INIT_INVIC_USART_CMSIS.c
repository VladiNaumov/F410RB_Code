/*  STM32_410RB initialization   */

// включить тактирование порта USART1
RCC->APB2ENR |=RCC_APB2ENR_USART1EN;

// включить тактирование GPIO
RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;

// включить тактирование альтернативных функций GPIO
RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;

// задать скорость обмена порта USART1=9600bd
USART1->BRR=0x1D4C;

//значение STOP = 0 соответствует 1 стоп-биту
USART1->CR2=~USART_CR2_STOP;

// разрешение работы RX/TX
USART1->CR1=~USART_CR1_RE | USART1_CR1_UE;


/*       Job             */

// передать байт данных 
USART1->DR = data;

// USART_SR_TC - это флаг (Transmission Complete), который указывает на то, что передача данных через USART завершена
while ((USART1->SR USART_SR_TC) == 0){}

//очистить флаг окончания передачи 
USART1=~USART_SR_TC;

// USART_SR_RXNE: Это константа флага, обозначающая, что входной буфер данных USART не пуст.
while((USART1->SR USART_SR_RXNE)==0){}

//считать принятый байт
temp = USART1->DR;


/* Interrupt mode
использование прерываний освобождает микроконтроллер  от необходимости 
постоянной проверки флагов и позволяет высвободить его ресурсы для других работ 
*/

#include "main.h"


uint32_t temp = 0;


/*  Interrupt mode */
void USART1_IRQHandler(void)
{
    /* USART2->SR: Это ссылка на регистр состояния USART1, где хранятся различные флаги состояния */

	/* USART_SR_RXNE: Это константа флага, обозначающая, что входной буфер данных USART не пуст. */
	if((USART1->SR & USART_SR_RXNE)!=0)
	{
		//считать принятый байт
		temp = USART1->DR;
		//выполнить какие то действия
	}
	/* USART_SR_TC - это флаг (Transmission Complete), который указывает на то, что передача данных через USART завершена */
	if((USART1->SR & USART_SR_TC)!=0)
	{
		// сбросить флаг
		USART1->SR=~USART_SR_TC;

	}

}
 main(void)
{



}

// разрешить прерывание от usart1
NVIC_EnabledRQ (USART1_IRQn);
// разрешит прерывание по окончание передачи 
USART1->CR1 |= USART1_CR1_ICE;
// разрешит прерывание поприему 
USART1->CR1 |= USART1_CR1_RXNEIE;

// разрешить прерывание от usart2 (HAL)
 HAL_NVIC_EnableIRQ(USART2_IRQn);





