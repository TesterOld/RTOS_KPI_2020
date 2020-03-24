#include "stm32f10x.h"                  
#include "misc.h"                       
#include "stm32f10x_tim.h"              
#include "GPIO_STM32F10x.h"             
#include "sysDelay.h"

// Arrays with a step
int shift_vals[] = {PIN_1A | PIN_2B, PIN_1A|PIN_1B, PIN_1B, PIN_1B | PIN_2A, PIN_2A, PIN_2A | PIN_2B, PIN_2B};


void init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//GPIO control init 
	RCC_APB2PeriphClockCmd(MOTOR_PORT_BUS, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = PIN_1A | PIN_2A | PIN_1B |PIN_2B;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(MOTOR_PORT , &GPIO_InitStructure);
		
	//TIMER INIT
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_InitStructure.TIM_Period = speed;
	TIM_InitStructure.TIM_Prescaler = PRESCALER;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	
	//NVIC — Nested vectored interrupt controller
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);  
}

int main(void){
	init();	
	while(1);
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//our code
		GPIO_ResetBits(MOTOR_PORT, PIN_1A | PIN_1B |PIN_2A | PIN_2B);
		GPIO_SetBits(MOTOR_PORT, shift_vals[substep_num]);
		if (clockwise){
			if (++substep_num == 7) 
				substep_num = 0; 
		}
		else{
			if (--substep_num == -1) 
				substep_num = 6;
		}	
	}
}
