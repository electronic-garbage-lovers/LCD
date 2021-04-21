#ifndef _STM32F10XGPIO_INIT_H_
#define _STM32F10XGPIO_INIT_H_
#define LED0 *((uint32_t *)( (GPIOB_BASE+0X0C-0X40000000)*32+5*4+0X42000000)) ////GPIOB_DOR bit5 add
#define LED1 *((uint32_t *)( (GPIOE_BASE+0X0C-0X40000000)*32+5*4+0X42000000)) ////GPIOE_DOR bit5 add
 
inline void Stm32f10xGpio_Init(void);
#endif
