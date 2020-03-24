#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define STEP_1 500
#define STEP_2 1000
#define STEP_3 2000

void delay_ms( uint32_t Val);
void btn_init_in_c15 (void);

//void delay_from_Brown(uint32_t nTime);
//void sys_tick_ini(void);

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

