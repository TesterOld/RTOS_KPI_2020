#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define BAUDRATE 9600

void UART_init(void);
void UART_send(char data[],unsigned char count);
void UART_dec(unsigned int val);
