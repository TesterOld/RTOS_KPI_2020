#include "stm32f10x.h"
#define STEP_1 500
#define STEP_2 1000
#define STEP_3 2000
// It is for B0 output blink 
/**
  * @brief  delay
  * @param  int delay is relativly delay 
  * @retval The input port pin value.
  */
void delay_(int i);

int main(void){
     const int period = 100000;
     int tau = 0;
     int sign = 1;
     // I. Enable PORTB Clock
		 RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
     // II. Enable  all low port B for output push-pool Mode
		 GPIOB -> CRL &= 0; 
     GPIOB -> CRL |= GPIO_CRL_MODE;
  
        for(;;){
               delay_(tau); 
                GPIOB -> ODR |= GPIO_ODR_ODR0;
              delay_(period - tau);// this plase control
                GPIOB -> ODR &= ~(GPIO_ODR_ODR0);
        // III. In this plase power control avtomatic
					tau += sign *STEP_3 ;
        
					if(tau >= period){
          tau = period;
          sign = -1;
          }
        else if (tau <= 0){
          tau = 0;
          sign = 1;
         }
              }
    }

void delay_(int del){
  unsigned int i = 0;
    for(i=0;i<del;i++){
      ;
      }
}
