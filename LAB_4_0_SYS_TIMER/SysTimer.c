#include "SysTimer.h"

void InitSysTimerAsMilliseconds(){	
	// Конфигурируем SysTick Timer. SystemCoreClock -  number of system clock cycles per second
	//SystemCoreClock / 1000 - каждую милисикунду таймер будет вызывать SysTick_Handler
	SysTick_Config(SystemCoreClock / 1000);
}

static __IO uint32_t TimingDelay;

void SysTick_Handler(void){
	if (TimingDelay != 0x00)
		TimingDelay --;
}
void Delay(uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}