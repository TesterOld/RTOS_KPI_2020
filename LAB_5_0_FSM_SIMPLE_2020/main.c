#include "delay.h"
#include "FSM.h"
#include "tm1637.h"
//keyboard
//C3 GPIOB9
//C2 GPIOB10
//C1 GPIOB11
//R4 GPIOB12
//R3 GPIOB13
//R2 GPIOB14
//R1 GPIOB15



int main()
{
	TM1637_init();
	TM1637_brightness(BRIGHTEST);
	TM1637_clearDisplay();
	
		while(1)
		{
			 delay_ms(250);
			_FSM_simple();
		}
}

