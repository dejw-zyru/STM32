/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <string.h>
#include "stm32f1xx.h"

#define z1

#ifdef z1

UART_HandleTypeDef uart;

void send_string(char* s){
	HAL_UART_Transmit(&uart, (uint8_t*)s, strlen(s), 1000);
}

int main(void)
{

	SystemCoreClock = 8000000; //taktowanie8MHz
	HAL_Init();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP; //wyjsice TX jako funkcja alternatywna push-pull
	gpio.Pin = GPIO_PIN_2;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_AF_INPUT; //wejsice RX jako funkcja alternatywna
	gpio.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio);

	//przygotawanie modulu USART2

	uart.Instance = USART2;
	uart.Init.BaudRate = 115200; //predkosc 115200
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);

	while (1){
		send_string("Hello world!\r\n");
		HAL_Delay(100);
	}
}

#endif
