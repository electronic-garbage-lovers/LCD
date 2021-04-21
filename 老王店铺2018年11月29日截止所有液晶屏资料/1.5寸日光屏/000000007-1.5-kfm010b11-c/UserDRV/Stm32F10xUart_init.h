#ifndef _STM32F10XUART_INIT_H_
#define _STM32F10XUART_INIT_H_
#include "stm32f10x.h"
void Stm32f10xUartInit(uint32_t SystemCLOCK,uint32_t Baud_RateSet);
void USART1_TX1BYTE(unsigned char data);
void printf_Str(void * str);

#include "stm32f10x.h"
#endif
