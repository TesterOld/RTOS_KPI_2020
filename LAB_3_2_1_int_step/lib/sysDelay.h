#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO

#define STEP_1 500
#define STEP_2 1000
#define STEP_3 2000

void delay_ms( uint32_t Val);
void btn_init_in_c15 (void);


#define	PIN_1A	GPIO_Pin_6
#define	PIN_1B	GPIO_Pin_7
#define PIN_2A	GPIO_Pin_8
#define PIN_2B	GPIO_Pin_9
#define MOTOR_PORT GPIOB
#define MOTOR_PORT_BUS RCC_APB2Periph_GPIOB

#define PRESCALER 8000 //1000 timer ticks per second
//one full step equals 1.8°, 360° = 200 steps
int step_count = 0;  //our halfstep = 0.9°,  360° = 400 steps  
int substep_num = 0;
//Maximum freq = 10 (100Hz)
int speed = 1000 ;//1000 ; //number of ticks before IRQ


bool clockwise = 1;
int degree = 0;

//0x7 = 0b1001
//0x3 = 0b0011
//0x2 = 0b0010
//0x6 = 0b0110
//0x4 = 0b0100
//0x8 = 0b1000