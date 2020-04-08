#include "keyboard.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "tm1637.h"
#include "delay.h"
// in this example key saved you state

char keypad[numRow][numCol]=
{
	'1','2','3',
	'4','5','6',
	'7','8','9',
	'*','0','#'
};

unsigned int row[numRow];
unsigned int col[numCol];
char oldKey=KEYPAD_NO_PRESSED;

void keypad_init(unsigned int cols[numCol],unsigned int rows[numRow]){ 
		unsigned int colSum=0;
		unsigned int rowSum=0;
		for(int i=0;i<numCol;i++)
		{
			col[i]=cols[i];
			colSum=colSum | col[i];
		}
		for(int i=0;i<numRow;i++)
		{
			row[i]=rows[i];
			rowSum=rowSum | row[i];
		}
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);// BUS is ON
    GPIO_InitTypeDef      KEYPAD_COL_B_STRUCT; 
		//Init columns 
    KEYPAD_COL_B_STRUCT.GPIO_Pin = colSum; // KEEP HARD PINS                                       
    KEYPAD_COL_B_STRUCT.GPIO_Mode = GPIO_Mode_Out_OD;
		KEYPAD_COL_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_COL_B_STRUCT);			
		// Init rows
		GPIO_InitTypeDef KEYPAD_ROW_B_STRUCT;
		KEYPAD_ROW_B_STRUCT.GPIO_Pin = rowSum; // KEEP HARD PINS 																				
		KEYPAD_ROW_B_STRUCT.GPIO_Mode = GPIO_Mode_IPU;
		KEYPAD_ROW_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_ROW_B_STRUCT);
}


char keypadGetKey(void)
{

	char res=KEYPAD_NO_PRESSED;
	for(int i=0;i<numCol;i++)
	{
		for(int k=0;k<numCol;k++)GPIO_SetBits(GPIOB, col[k]); 															//Set all columns
		GPIO_ResetBits(GPIOB, col[i]);																											//Reset column which check now
		for(int k=0;k<numRow;k++)if(!GPIO_ReadInputDataBit(GPIOB, row[k]))res=keypad[k][i]; //Check all rows
	}
	if(res != oldKey) //if key is difference with old key
	{
		oldKey=res;
		return res;
	}
	
	return KEYPAD_NO_PRESSED;//old
	
}
