#ifndef _FSM_1_H
#define _FSM_1_H
#include "stm32f10x.h"
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "keyboard.h"
#define FSM_FAST 10
#define FSM_SLOW 700
#define FSM_TOO_SLOW 1000



// This is for kyboard library no edit !!!!
struct State{
char STATE_2;//48 -2
char STATE_RES;//55 -55 
char STATE_0;//50 - 0 
char STATE_SNESHINKA;//51 - 99  
char STATE_9;//52 - 9 
char STATE_8;//53 - 8 
char STATE_7;//54 - 7 
char STATE_6;//55 - 6
char STATE_5;//56 - 5
char STATE_4;//57 - 4 
char STATE_3;//51 - 3
char STATE_1;//35 -1
				};





#endif				


