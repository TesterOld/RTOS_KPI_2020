#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
/**
  * @brief Real delay function with interrupt SysTick_Handler 
  * @param Unsigned int -> uint32_t,  nTime ms delay 
  * @retval no
  */
void Delay(uint32_t nTime);

int main(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
// Enable Peripheral Clocks for GPIO
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

// Configure Pins 
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
// Configure SysTick Timer. Every 1 msec, the timer triggers a call to the SysTick_Handler
    if (SysTick_Config(SystemCoreClock / 1000))
        while (1);

    while (1) { 
      GPIO_SetBits(GPIOB, GPIO_Pin_0);
    	Delay(250); // wait 250ms
    	/* Reset  PC13*/
    	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    	Delay(250); // wait 250ms
    }
}


static __IO uint32_t TimingDelay;


void Delay(uint32_t nTime)
{ 
    TimingDelay = nTime;
    while(TimingDelay != 0);
}
// Interrupt function SysTick
void SysTick_Handler(void)
{
    if (TimingDelay != 0x00)
        TimingDelay--;
}

// if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15))// Catch from GND 
//		{//slow, press and connect GPIOC 13 to GND 
//		 led_toggled_brown();
//         delay_from_Brown(1000);
//         return 1;
//		}
//		
//		else 
//        {//fast no press !!!
//        led_toggled_brown();
//        delay_from_Brown(100);
//        return 0;    
//        }