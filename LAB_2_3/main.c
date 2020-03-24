#include "stm32f10x.h"
#define POW_SLOW      1000000 //
#define POW_FAST      100000
// It is for B0 output blink 
/**
  * @brief  delay
  * @param  int delay is relativly delay 
  * @retval The input port pin value.
  */
void delay_(int i);

int main(void){ 
      // I. Enable PORTB Clock    
      RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
			// II. Enable  all low port B for output push-pool Mode
      GPIOB -> CRL &= 0; 
      GPIOB -> CRL |= GPIO_CRL_MODE; 
  
        for(;;){
               delay_(POW_SLOW); 
                GPIOB -> ODR |= GPIO_ODR_ODR0;// pin B0 on
              delay_(POW_SLOW);// this plase control
                GPIOB -> ODR &= ~(GPIO_ODR_ODR0);// pin B0 off
              }
    }

void delay_(int del){
  int i = 0;
    for(i=0;i<del;i++){
      ;
      }
}


//#include "stm32f10x.h"
//void delay_(int i);

//int main(void){
//    unsigned const int period = 100000;
//      int tau = 0;
//    int sign = 1;
//      RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
//      GPIOB -> CRL &= 0; 
//      GPIOB -> CRL |= GPIO_CRL_MODE;
//  
//        for(;;){
//               delay_(tau); 
//                GPIOB -> ODR |= GPIO_ODR_ODR0;
//              delay_(period - tau);// this plase control
//                GPIOB -> ODR &= ~(GPIO_ODR_ODR0);
//        tau += sign * 500;
//        if(tau >= period){
//          tau = period;
//          sign = -1;
//          }
//        else if (tau <= 0){
//          tau = 0;
//          sign = 1;
//         }
//              }
//    }

//void delay_(int del){
//  int i = 0;
//    for(i=0;i<del;i++){
//      ;
//      }
//}
