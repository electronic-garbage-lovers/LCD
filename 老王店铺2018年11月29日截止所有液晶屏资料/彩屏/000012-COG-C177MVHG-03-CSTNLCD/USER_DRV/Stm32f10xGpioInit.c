#include "stm32f10x.h"


void Stm32f10xGpioInit(void)
{
//��01->GPIOC 0-7�������
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;//IO�˿�Cʱ��ʹ��  
  
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
 	
	GPIOC->ODR =0XFFFF;
//��02->GPIOb 8-16�������
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;//IO�˿�Cʱ��ʹ��  
  
	GPIOB->CRH  |= GPIO_CRH_MODE8 | 
	               GPIO_CRH_MODE9 |
	                GPIO_CRH_MODE10 |	
 	                 GPIO_CRH_MODE11 |
	                  GPIO_CRH_MODE12 |	
	                   GPIO_CRH_MODE13 |	
	                    GPIO_CRH_MODE14 |
	                     GPIO_CRH_MODE15;
		GPIOB->CRH &=~ (
	                   GPIO_CRH_CNF8 |
										 GPIO_CRH_CNF9 |
										 GPIO_CRH_CNF10 |
										 GPIO_CRH_CNF11 |
										 GPIO_CRH_CNF12 |
										 GPIO_CRH_CNF13 |
										 GPIO_CRH_CNF14 |
										 GPIO_CRH_CNF15  );	

 	GPIOB->ODR =0XFFFF;
	
//��02->GPIOA  
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;//IO�˿�Aʱ��ʹ��  
	/****** LED0->GPIOA.BIT8 ******/
	GPIOA->CRH |= GPIO_CRH_MODE8;//GPIOA-bit8 �������ٶ�Ϊ50MHz 
	GPIOA->CRH &=~GPIO_CRH_CNF8;//GPIOA-bit8�������
}
