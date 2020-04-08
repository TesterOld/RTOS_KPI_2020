#include "UART.h"
#include "delay.h"

GPIO_InitTypeDef port;
USART_InitTypeDef usart;

void UART_init(void)
{
	//Включаем тактирование
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
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
    USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART1_IRQn);
	
		port.GPIO_Pin = GPIO_Pin_8;
		port.GPIO_Mode = GPIO_Mode_Out_PP;
		port.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &port);
}

void UART_send(char data[],unsigned char count)
{
	delay_ms(2);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	delay_ms(2);
	for(unsigned char i=0;i<count;i++)
	{
		USART_SendData(USART1,data[i]);
		delay_ms(2);
	}
	delay_ms(2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void UART_dec(unsigned int val)
{
	char buff[10]={0,0,0,0,0,0,0,0,0,0};
	sprintf(buff,"%d\r\n",val);
	int i=0;
	delay_ms(2);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	delay_ms(2);
	while(buff[i]!=0 && i<10)
	{
		USART_SendData(USART1,buff[i]);
		delay_ms(2);
		i++;
	}
	delay_ms(2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}
