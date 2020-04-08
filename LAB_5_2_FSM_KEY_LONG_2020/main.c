#include "keyboard.h"
#include "tm1637.h"
#include "delay.h"
#include "FSM_1.h"

#define _KEYPAD_NO_PRESSED1 0xFF
// This is for kyboard library no edit !!!!
const struct State NState ={'0','1','2','3','4','5','6','7','8','9','*','#' };
uint32_t CurrentState ='0';

char handle_state_0(void){TM1637_clearDisplay(); TM1637_display(0,0); return '1';}
char handle_state_1(void){TM1637_clearDisplay(); TM1637_display(0,1);return '1';}
char handle_state_2(void){TM1637_clearDisplay(); TM1637_display(0,2);return '1';}
char handle_state_3(void){TM1637_clearDisplay(); TM1637_display(0,3);return '1';}
char handle_state_4(void){TM1637_clearDisplay(); TM1637_display(0,4);return '1';}
char handle_state_5(void){TM1637_clearDisplay(); TM1637_display(0,5);return '1';}
char handle_state_6(void){TM1637_clearDisplay(); TM1637_display(0,6);return '1';}
char handle_state_7(void){TM1637_clearDisplay(); TM1637_display(0,7);return '1';}
char handle_state_8(void){TM1637_clearDisplay(); TM1637_display(0,8);return '1';}
char handle_state_9(void){TM1637_clearDisplay(); TM1637_display(0,9);return '1';}
char handle_state_sneshinka(void){TM1637_clearDisplay(); TM1637_display_all(99);return '1';}
char handle_state_res(void){TM1637_clearDisplay(); TM1637_display_all(55);return '1';}

uint32_t _FSM_simple(void) {
          
			   if(NState.STATE_0 == CurrentState)
					{
								
								handle_state_0();
								CurrentState=NState.STATE_0;
								delay_ms(FSM_SLOW);
								return 0;
									
					}
					if(NState.STATE_1 == CurrentState)
					{
								
								handle_state_1();
								CurrentState=NState.STATE_1;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_2 == CurrentState)
					{
								
								handle_state_2();
								CurrentState=NState.STATE_2;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_3 == CurrentState)
					{
								handle_state_3();
								CurrentState=NState.STATE_3;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_4 == CurrentState)
					{
								handle_state_4();
								CurrentState=NState.STATE_4 ;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_5 == CurrentState)
					{
								handle_state_5();
								CurrentState=NState.STATE_5;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_6 == CurrentState)
					{
								handle_state_6();
								CurrentState=NState.STATE_6;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_7 == CurrentState)
					{
								handle_state_7();
								CurrentState=NState.STATE_7;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_8 == CurrentState)
					{
								handle_state_8();
								CurrentState=NState.STATE_8;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_9 == CurrentState)
					{
								handle_state_9();
								CurrentState=NState.STATE_9;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					if(NState.STATE_SNESHINKA == CurrentState)
					{
								handle_state_sneshinka();
								CurrentState=NState.STATE_SNESHINKA;
								delay_ms(FSM_SLOW);
								return 0;
					}
					if(NState.STATE_RES == CurrentState)
					{
								handle_state_res();
								CurrentState=NState.STATE_RES;
								delay_ms(FSM_SLOW);
								return 0;	
					}
					delay_ms(300);
					//display KEYPAD_NO_PRESSED1;
					TM1637_display_all(77);
						return 0;
				
}



int main()
{
	keypad_init((unsigned int[3]){GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11},(unsigned int[4]){GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15});
	TM1637_init();
	TM1637_brightness(BRIGHTEST);
	
		while (1)
		{
			CurrentState=keypadGetKey();
			_FSM_simple();
			
	}
}



