#include "stm32f10x.h"
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//SysTick clock set to 3 MHz (max HCLK/8)
#define _SECOND  250
#define PINS_A GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
#define FORVARD_    0
#define BACKVARD_ 1
#define  _KEYPAD_NO_PRESSED 0xFF

uint32_t init_sys_timer(void);
void rotate(void);
void gpio_init (void);
void delay(int time); 

// Keyboard function
void init_keyboard(void);
void init_car(void);
uint8_t keypadGetKey(void);
void handleKeyPress_if(uint8_t key); 
void handleKeyPress_switch(uint8_t key);

#define KEYPAD_NO_PRESSED 0xFF

//State fn
#define RIGHT '0'
#define STOP '1'
#define FORWARD '2'
#define _STATE_3 '3'
#define _STATE_4 '4'
#define BACKWARD '5'
#define _STATE_6 '6'
#define _STATE_7 '7'
#define LEFT '8'
#define _STATE_9 '9'
#define _STATE_SNESHINKA  '*'
#define _STATE_RES  '#'

//State pins
#define _STATE_0_PINS 0x0001
#define _STATE_1_PINS GPIO_Pin_7
#define _STATE_2_PINS GPIO_Pin_6
#define _STATE_3_PINS GPIO_Pin_7 | GPIO_Pin_6
#define _STATE_4_PINS GPIO_Pin_5
#define _STATE_5_PINS GPIO_Pin_7 | GPIO_Pin_5
#define _STATE_6_PINS GPIO_Pin_6 | GPIO_Pin_5
#define _STATE_7_PINS GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_7
#define _STATE_8_PINS GPIO_Pin_4
#define _STATE_9_PINS GPIO_Pin_4 | GPIO_Pin_7
#define _STATE_SNESHINKA_PINS  '*'
#define _STATE_RES_PINS  '#'

//State inependent from keyboard 
#define _NEW_STATE_0 0xA0
#define _NEW_STATE_1 0xA1
#define _NEW_STATE_2 0xA2
#define _NEW_STATE_3 0xA3


//Keyboard states 
void _init_state(void);
void forward(void);
void backward(void);
void left(void);
void right(void);
void stop(void);

//--
void _FSM_car(void) ;
