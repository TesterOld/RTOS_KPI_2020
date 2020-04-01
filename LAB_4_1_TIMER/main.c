#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "TIMERS.h"

//http://www.minokasago.org/STM32wiki/index.php?NVIC_IRQChannel

void TIM1_UP_IRQHandler()// Not worked
{
	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		GPIOA->BSRR = GPIO_Pin_4;//A4 red
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
void TIM2_IRQHandler()
{
    GPIOA->ODR ^= GPIO_Pin_6;
    // Clears the TIM2 interrupt pending bit
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
}
void TIM3_IRQHandler()
{
	
	GPIOA->ODR ^= GPIO_Pin_7;
    // Clears the TIM2 interrupt pending bit
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
}
void TIM4_IRQHandler()
{
	// Checks whether the TIM2 interrupt has occurred or not
	if (TIM_GetITStatus(TIM4, TIM_IT_Update))
	{
	    GPIOA->ODR ^= GPIO_Pin_5;
         // Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}




void GPIO_Init_(void);

int main(void)
{
	DelayInit();
	TIM1_INT_Init();// Not worked
    TIM2_INT_Init();
    TIM3_INT_Init();
	TIM4_INT_Init();
	GPIO_Init_();
	
	
	while (1)
	{
		// Blink LED on PC13 for all sys testing 
		GPIOC->BRR = GPIO_Pin_13;
	    DelayMs(2500);
		GPIOC->BSRR = GPIO_Pin_13;
        DelayMs(2500);
       
	}
}

void GPIO_Init_(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    // Initialize PB12 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);    
    
}

