#include "stm32f10x.h"                  
#include "stm32f10x_tim.h"              
#include "GPIO_STM32F10x.h"             


#define PRESCALER 8000 //1000 timer ticks per second
int period_speed = 1000 ;


void Setup(){
	
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//TIMER INIT---
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_InitStructure.TIM_Period = period_speed;
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
	Setup();
	
	while(1)
	{
		;
	}
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//user code
	}
}
