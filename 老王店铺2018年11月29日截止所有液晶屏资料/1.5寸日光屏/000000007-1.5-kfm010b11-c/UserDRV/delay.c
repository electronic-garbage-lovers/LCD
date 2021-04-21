//72mhz/48mhz(->1ms)
#include "stm32f10x.h"
//clock72mhz
void delay_1ms(volatile uint32_t delay)
{
	unsigned int temp;
	for(;delay>0;delay--)
	for(temp=0;temp<10280;temp++);
}



 
