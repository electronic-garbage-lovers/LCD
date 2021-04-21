#include "stm32f10x.h"
void stm32f10x_AFIO(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;//辅助功能IO时钟使能 (Alternate function I/O clock enable)
	AFIO->MAPR &= ~((1<<24) | (1<<25) |(1<<26));//cls24-26
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;//010：关闭JTAG-DP，启用SW-DP；
}
