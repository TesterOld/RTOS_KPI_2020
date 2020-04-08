#ifndef USART_H
#define USART_H
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void init_usart(void);

void usart_send_symbol(uint16_t data);

#endif
