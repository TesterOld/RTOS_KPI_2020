#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#define BUF_SIZE 128 //размер буфера обязательно равен степени двойки!
#define BUF_MASK (BUF_SIZE-1)

#define BAUDRATE 9600


void Send(char data[],int count);
void delay_us( uint32_t Val);
void delay_ms( uint32_t Val);

GPIO_InitTypeDef port;
USART_InitTypeDef usart;

unsigned char PC_dxIN = 0, PC_dxOUT = 0;
char buffer_from_PC [BUF_SIZE];

unsigned char rIN = 0, rOUT = 0;
char rBuffer [BUF_SIZE];



void init()
{
	GPIO_InitTypeDef port;
    
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    //Настраиваем вывод
		port.GPIO_Pin = GPIO_Pin_13;  
    port.GPIO_Mode = GPIO_Mode_Out_PP;   
    port.GPIO_Speed = GPIO_Speed_2MHz;   
    GPIO_Init(GPIOC, &port);
	}




void USART1_IRQHandler()
{
    //Проверяем, действительно ли прерывание вызвано приемом нового байта
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {	
		buffer_from_PC[PC_dxIN++] = USART_ReceiveData(USART1);	
		PC_dxIN &= BUF_MASK; 
    }
}




void initAll()
{
    //Включаем тактирование
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 
    //Пины PA9 и PA10 в режиме альтернативных функций –
    //Rx и Tx USART’а
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_9;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    port.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    port.GPIO_Pin = GPIO_Pin_10;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    //Настройка USART, все поля оставляем дефолтными, кроме скорости обмена
    USART_StructInit(&usart);
    usart.USART_BaudRate = BAUDRATE;
    USART_Init(USART1, &usart);
	
	
	
}
 






int main()
{
    __enable_irq ();
    initAll();
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
    NVIC_EnableIRQ(USART1_IRQn);
		init();
    delay_ms(100);
		char i=48;
		USART_SendData(USART1,i);
		delay_ms(2);
		USART_SendData(USART1,i);
		delay_ms(2);
		USART_SendData(USART1,i);
		delay_ms(2);
	while (1)
	{
		if (rIN != rOUT)
		{
			unsigned char buf=rBuffer[rOUT++];
			USART_SendData(USART1,buf);
			rOUT &= BUF_MASK;
		}
		else if (PC_dxIN != PC_dxOUT)
		{
		  unsigned char buf_temp;
		  buf_temp = buffer_from_PC[PC_dxOUT++];
		  PC_dxOUT &= BUF_MASK;
		  USART_SendData(USART1,buf_temp);
		  delay_us(300);
		}		
		else 
		delay_us(1000);
		
	}
}
 


 
void Send(char data[],int count)
{
	for(int i=0;i<count;i++)
	{
		USART_SendData(USART1,data[i]);
	}
}


void delay_us( uint32_t Val) 
{
	Val=Val*10;
  for( ; Val != 0; Val--) 
  		{
		__nop();
  		}
}

void delay_ms( uint32_t Val) 
{
	Val=Val*10000;
	for( ; Val != 0; Val--) 
  		{
		__nop();
  		}
}