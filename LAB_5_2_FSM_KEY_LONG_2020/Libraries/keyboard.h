#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//=================================
//
//  Connect to keyboard as following:
//
//  PORT B - 9 10 11 12  13 14 15
//					 ^	^	 ^  ^
//
//=================================

// GPIOB
//keyboard
//C3 GPIOB9
//C2 GPIOB10
//C1 GPIOB11
//R4 GPIOB12
//R3 GPIOB13
//R2 GPIOB14
//R1 GPIOB15

#define KEYPAD_NO_PRESSED 0xFF
#define numRow 4
#define numCol 3

void keypad_init(unsigned int cols[numCol],unsigned int rows[numRow]);

char keypadGetKey(void);
#endif