#include "stm32f10x.h"


void Stm32f10xGpioInit(void)
{
//●01->GPIOC 0-7推挽输出
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;//IO端口C时钟使能  
  
	GPIOC->CRL |= GPIO_CRL_MODE0 | 
	               GPIO_CRL_MODE1 |
	                GPIO_CRL_MODE2 |	
 	                 GPIO_CRL_MODE3 |
	                  GPIO_CRL_MODE4 |	
	                   GPIO_CRL_MODE5 |	
	                    GPIO_CRL_MODE6 |
	                     GPIO_CRL_MODE7;
		GPIOC->CRL &=~ (
	                   GPIO_CRL_CNF0 |
										 GPIO_CRL_CNF1 |
										 GPIO_CRL_CNF2 |
										 GPIO_CRL_CNF3 |
										 GPIO_CRL_CNF4 |
										 GPIO_CRL_CNF5 |
										 GPIO_CRL_CNF6 |
										 GPIO_CRL_CNF7  );
}
