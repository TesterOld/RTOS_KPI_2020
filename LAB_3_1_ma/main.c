#include "lib.h"

uint32_t state =_KEYPAD_NO_PRESSED;

uint32_t init_sys_timer(void) {
		// SysTic init 
		RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);
		return SysTick_Config(RCC_Clocks.HCLK_Frequency / _SECOND); /* Configure SysTick to generate an interrupt every millisecond */
}

void delay(int time) {
	for (int i = 0; i < time; i++);
}

//Keyboard states 
void _init_state(void){
  GPIO_ResetBits (GPIOA, PINS_A);
  GPIO_SetBits(GPIOA, PINS_A);  
}

void forward(void){
		GPIO_ResetBits (GPIOA, PINS_A);
		GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2); // forward
		return;
}
void backward(void){
    GPIO_ResetBits (GPIOA, PINS_A);
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3); // backward
		return;
}
void left(void){
    GPIO_ResetBits (GPIOA, PINS_A);
    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3); // left
		return;
}
void right(void){
    GPIO_ResetBits (GPIOA, PINS_A);
    GPIO_SetBits(GPIOA,  GPIO_Pin_1 | GPIO_Pin_2); // right
		return;
}
void stop(void){
    GPIO_ResetBits (GPIOA, PINS_A);
		return;
}


void _FSM_car(void) {
               
		switch (state)  {
				case STOP: 
						stop();
						state = KEYPAD_NO_PRESSED;
						break;
				case FORWARD: // forward
						forward();
						state = FORWARD;
						break;
				case BACKWARD: // backward
						backward();
						state = BACKWARD;
						break;
				case LEFT: // left
						left();
						state = LEFT;
						break;
			  case RIGHT: // right
						right();
						state = RIGHT;
						break;
				default:
						state = KEYPAD_NO_PRESSED; 
						break;
		}
}


void init_keyboard(void){
	
    // ENABLE BUS B
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
		// OUT PINS CONF (keyboard)
    GPIO_InitTypeDef KEYPAD_COL_B_STRUCT;
    KEYPAD_COL_B_STRUCT.GPIO_Pin =     GPIO_Pin_13 |
                                       GPIO_Pin_14 |
                                       GPIO_Pin_15;
    KEYPAD_COL_B_STRUCT.GPIO_Mode = GPIO_Mode_Out_OD;
		KEYPAD_COL_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_COL_B_STRUCT);
    
    // IN PINS CONF (keyboard)
    GPIO_InitTypeDef KEYPAD_ROW_B_STRUCT;
		KEYPAD_ROW_B_STRUCT.GPIO_Pin =     GPIO_Pin_12 |
                                       GPIO_Pin_11 |
                                       GPIO_Pin_10 |
                                       GPIO_Pin_9;
		KEYPAD_ROW_B_STRUCT.GPIO_Mode = GPIO_Mode_IPU;
		KEYPAD_ROW_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_ROW_B_STRUCT);
}


void init_car(void){
	
    // ENABLE BUS A
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
		// OUT PINS CONF (info)
    GPIO_InitTypeDef DISPLAY_A_STRUCT;
    DISPLAY_A_STRUCT.GPIO_Pin =     GPIO_Pin_0 |     
                                    GPIO_Pin_1 |
                                    GPIO_Pin_2 |
                                    GPIO_Pin_3 |     
                                    GPIO_Pin_4 |
                                    GPIO_Pin_5 |     
                                    GPIO_Pin_6 |
                                    GPIO_Pin_7;
    DISPLAY_A_STRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
		DISPLAY_A_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &DISPLAY_A_STRUCT);
}


uint8_t keypadGetKey(void)
{
		// Scan column 0 (column 0 pin is grounded, other column pins is open drain)
		GPIO_ResetBits(GPIOB, GPIO_Pin_13); // 13
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		// Read rows
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				return '1';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
				return '4';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
				return '7';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
				return '*';
			
		// Scan column 1 (column 1 pin is grounded, other column pins is open drain)
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14); // 14
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		// Read rows
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				return '2';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
				return '5';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
				return '8';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
				return '0';
			
		// Scan column 2 (column 2 pin is grounded, other column pins is open drain)
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15); // 15
		// Read rows
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				return '3';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
				return '6';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
				return '9';
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
				return '#';
		
		return state;
}


void SysTick_Handler(void) {                             /* SysTick interrupt Handler. */
		state = keypadGetKey();
}

int main() {
		uint32_t success_timer = init_sys_timer();
		
		init_keyboard();
		init_car();
		
		while(!success_timer && 1) {
			_FSM_car();
		} 
}
