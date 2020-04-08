#include "keyboard.h"
#include "tm1637.h"
#include "delay.h"
#include "FSM_1.h"
#include "usart.h"

char CurrentState = '0';

void handle_digit(int8_t digit)
{
	TM1637_clearDisplay();
	TM1637_display(0, digit);
	usart_send_symbol(CurrentState);
	delay_ms(FSM_SLOW);
}

void handle_special(int16_t decimal)
{
	TM1637_clearDisplay();
	TM1637_display_all(decimal);
	usart_send_symbol(CurrentState);
	delay_ms(FSM_SLOW);
}

void _FSM_simple(void)
{
	if(CurrentState <= '9' && CurrentState >= '0')
	{
		handle_digit(CurrentState - '0');
		return;
	}
	
	if(CurrentState == '*')
	{
		handle_special(99);
		return;
	}
	
	if(CurrentState == '#')
	{
		handle_special(55);
		return;
	}
	
	delay_ms(300);
	//display KEYPAD_NO_PRESSED1;
	TM1637_display_all(77);
}

int main()
{
  init_usart();
	
	keypad_init((unsigned int[3]){GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11},(unsigned int[4]){GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15});
	TM1637_init();
	TM1637_brightness(BRIGHTEST);
	
	while (1)
	{
		CurrentState = keypadGetKey();
		_FSM_simple();
	}
}
