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

//--------------------------
/**
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
//__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
//{
//  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
//  {
//    return (1UL);                                                   /* Reload value impossible */
//  }

//  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
//  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
//  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
//  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
//                   SysTick_CTRL_TICKINT_Msk   |
//                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
//  return (0UL);                                                     /* Function successful */
//}

