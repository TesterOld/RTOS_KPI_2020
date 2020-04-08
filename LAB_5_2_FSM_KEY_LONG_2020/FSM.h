#include "stm32f10x.h"
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


//SysTick clock set to 3 MHz (max HCLK/8)
#define _SECOND  250
#define _KEYPAD_NO_PRESSED 0xFF

// This is for kyboard library no edit !!!!
struct State{
char STATE_0;
char STATE_1;
char STATE_2;
char STATE_3;
char STATE_4;
char STATE_5;
char STATE_6;
char STATE_7;
char STATE_8;
char STATE_9;
char STATE_SNESHINKA;
char STATE_RES;
				};



uint32_t init_sys_timer(void);
uint32_t _FSM_simple(void);

char handle_state_0(void);
char handle_state_1(void);
char handle_state_2(void);
char handle_state_3(void);
char handle_state_4(void);
char handle_state_5(void);
char handle_state_6(void);
char handle_state_7(void);
char handle_state_8(void);
char handle_state_9(void);
char handle_state_sneshinka(void);
char handle_state_res(void);

				