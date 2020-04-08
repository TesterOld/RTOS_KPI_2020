#include "delay.h"

void delay_us( unsigned long Val) 
{
	Val=Val*10;
  for( ; Val != 0; Val--) 
  		{
		__nop();
  		}
}

void delay_ms( unsigned long Val) 
{
	Val=Val*10000;
	for( ; Val != 0; Val--) 
  		{
		__nop();
  		}
}
