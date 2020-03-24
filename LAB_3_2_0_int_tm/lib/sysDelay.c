#include "sysDelay.h"

void delay_ms( uint32_t Val) 
{
	Val=Val*10000;
	for( ; Val != 0; Val--) 
  		{
		__nop();
  		}
}

void btn_init_in_c15 (void){
    
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}



//static __IO uint32_t TimingDelay;

//void sys_tick_ini(void){
//if (SysTick_Config(SystemCoreClock / 1000))
//            while (1);
//}
//void delay_from_Brown(uint32_t nTime){
//    TimingDelay = nTime;
//    while(TimingDelay != 0);
//}

//void SysTick_Handler(void){
//    if (TimingDelay != 0x00)
//        TimingDelay --;
//}