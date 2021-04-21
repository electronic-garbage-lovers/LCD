//72mhz/48mhz(->1ms)
#include "stm32f10x.h" 

void delay_1ms(volatile uint32_t delay)
{
	unsigned int temp;
	for(;delay>0;delay--)
	for(temp=0;temp<7997;temp++);
}


void delay_100us(volatile uint32_t delay)
{
	unsigned int temp;
	for(;delay>0;delay--)
	for(temp=0;temp<792;temp++);
}







/*


48mhz
void delay_100us(volatile uint32_t delay)
{
	unsigned int temp;
	for(;delay>0;delay--)
	for(temp=0;temp<925;temp++);
}

//..................................................

__ASM void nop(void )//__ASM("NOP");	

{
  nop ;
}
*/
