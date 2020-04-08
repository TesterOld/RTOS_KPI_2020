#include "FSM.h"
#include "tm1637.h"
// This is for kyboard library no edit !!!!
const struct State NState ={'0','1','2','3','4','5','6','7','8','9','*','#' };
uint32_t CurrentState ='0';

uint32_t init_sys_timer(void) {
		// SysTic init 
		RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);
		return SysTick_Config(RCC_Clocks.HCLK_Frequency / _SECOND); /* Configure SysTick to generate an interrupt every millisecond */
}

//Keyboard states 


uint32_t _FSM_simple(void) {
               
			   if(NState.STATE_0 == CurrentState)
					{
								
								handle_state_0();
								CurrentState=NState.STATE_1;
								return 0;
									
					}
					if(NState.STATE_1 == CurrentState)
					{
								
								handle_state_1();
								CurrentState=NState.STATE_2;
								return 0;	
					}
					if(NState.STATE_2 == CurrentState)
					{
								
								handle_state_2();
								CurrentState=NState.STATE_3;
								return 0;	
					}
					if(NState.STATE_3 == CurrentState)
					{
								handle_state_3();
								CurrentState=NState.STATE_4;
								return 0;	
					}
					if(NState.STATE_4 == CurrentState)
					{
								handle_state_4();
								CurrentState=NState.STATE_5;
								return 0;	
					}
					if(NState.STATE_5 == CurrentState)
					{
								handle_state_5();
								CurrentState=NState.STATE_6;
								return 0;	
					}
					if(NState.STATE_6 == CurrentState)
					{
								handle_state_6();
								CurrentState=NState.STATE_7;
								return 0;	
					}
					if(NState.STATE_7 == CurrentState)
					{
								handle_state_7();
								CurrentState=NState.STATE_8;
								return 0;	
					}
					if(NState.STATE_8 == CurrentState)
					{
								handle_state_8();
								CurrentState=NState.STATE_9;
								return 0;	
					}
					if(NState.STATE_9 == CurrentState)
					{
								handle_state_9();
								CurrentState=NState.STATE_SNESHINKA;
								return 0;	
					}
					if(NState.STATE_SNESHINKA == CurrentState)
					{
								handle_state_9();
								CurrentState=NState.STATE_RES;
								return 0;
					}
					if(NState.STATE_RES == CurrentState)
					{
								handle_state_9();
								CurrentState=NState.STATE_0;
								return 0;	
					}
					
					//CurrentState=_KEYPAD_NO_PRESSED;
						return 0;
}




void SysTick_Handler(void) {                             /* SysTick interrupt Handler. */
		;
}


char handle_state_0(void){TM1637_clearDisplay(); TM1637_display(0,0); return '1';}
char handle_state_1(void){TM1637_clearDisplay(); TM1637_display(0,1);return '1';}
char handle_state_2(void){TM1637_clearDisplay(); TM1637_display(0,2);return '1';}
char handle_state_3(void){TM1637_clearDisplay(); TM1637_display(1,3);return '1';}
char handle_state_4(void){TM1637_clearDisplay(); TM1637_display(1,4);return '1';}
char handle_state_5(void){TM1637_clearDisplay(); TM1637_display(2,5);return '1';}
char handle_state_6(void){TM1637_clearDisplay(); TM1637_display(2,6);return '1';}
char handle_state_7(void){TM1637_clearDisplay(); TM1637_display(2,7);return '1';}
char handle_state_8(void){TM1637_clearDisplay(); TM1637_display(3,8);return '1';}
char handle_state_9(void){TM1637_clearDisplay(); TM1637_display(3,9);return '1';}
char handle_state_sneshinka(void){TM1637_clearDisplay(); TM1637_display(1,0);return '1';}
char handle_state_res(void){TM1637_clearDisplay(); TM1637_display(1,1);return '1';}

