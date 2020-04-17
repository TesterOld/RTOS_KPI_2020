#include "usart.h"

#define BUF_SIZE 128
#define BUF_MASK (BUF_SIZE-1)

#define BAUDRATE 9600

GPIO_InitTypeDef port;
USART_InitTypeDef usart;

unsigned char PC_index_IN = 0, PC_index_OUT = 0;
char PC_BUFFER [BUF_SIZE];

void USART1_IRQHandler()
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {	
			PC_BUFFER[PC_index_IN++] = USART_ReceiveData(USART1);	
			PC_index_IN &= BUF_MASK; 
    }
}

void init_usart()
{
		__enable_irq();
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_9;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    port.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    port.GPIO_Pin = GPIO_Pin_10;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    USART_StructInit(&usart);
    usart.USART_BaudRate = BAUDRATE;
    USART_Init(USART1, &usart);
	
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//Enables or disables the specified USART interrupts.
		USART_Cmd(USART1, ENABLE);
		NVIC_EnableIRQ(USART1_IRQn);
}

void usart_send_symbol(uint16_t data)
{
	USART_SendData(USART1, data);
}
