## STM32 NUCLEO-410RB

- ch00 example/experience
- ch01 GPIO (blink)
- ch02 GPIO (but)
- ch03 GPIO (but/lock)
- ch04 UART(USART) - Interrupt mode 
- ch05 UART(USART) - Interrupt mode
- ch06 DMA Direct Memory Access

- F410_CMSIS default project


## 

- UART/USART (Universal asynchronous receiver/transmitter) -универсальный асинхронный приемопередатчик.
- NVIC Контроллер –это специальный аппаратный модуль внутри микроконтроллеров на базе Cortex-M, отвечающий за обработку прерываний (interrupts).
- EXTI Контроллер внешних прерываний/событий (interrupts/events) -отвечает за взаимосвязь между внешними сигналами I/O и контроллером NVIC.
- DMA Direct Memory Access – прямой доступ к памяти.
- RCC тактирование и HCI генератор
- таймеры (timers)
- АЦП (ADC) 
- ЦАП (DAC)
- I2C
- SPI
- циклический контроль избыточности (cyclic redundancy check - CRC)
- независимый  оконный сторожевойа таймер (IWDG, WWDG)
- часы реального времени (real time clock RTC)

## 

Порядок инициализации STM32F410RB (пример в каталоге ch00/configuration/main.c)

1. Запуск отладчика SYS (Serial Wire) - DBG (Debug support)
2. Запуск тактирования - RCC (Crystal ceramic resonator)
2. Инициализация портов - (GPIOA, GPIOB, GPIOC, GPIOH)


INFO:
UART_MODE_RX: вход принимаемых данных. 
TUART_MODE_TX: выход передаваемых данных. 

## License

- https://www.st.com/content/st_com/en/shortcuts.html
