#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>


void InitSysTimerAsMilliseconds();

void SysTick_Handler(void);

void Delay(uint32_t nTime);