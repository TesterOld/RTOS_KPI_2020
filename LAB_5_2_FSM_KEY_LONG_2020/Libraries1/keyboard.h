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

#define KEYPAD_NO_PRESSED 0xFF
#define numRow 4
#define numCol 3

void keypad_init(unsigned int cols[numCol],unsigned int rows[numRow]);

char keypadGetKey(void);
