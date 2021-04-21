#include "configALL.H"
void Stm32f10xGpio_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
	                 |RCC_APB2ENR_IOPBEN
									  |RCC_APB2ENR_IOPDEN
									   |RCC_APB2ENR_IOPEEN
										   |RCC_APB2ENR_IOPCEN
									    |RCC_APB2ENR_IOPGEN ;
	
	
 //PA9+PA10 uart1复用推挽模式
  GPIOA->CRH |= GPIO_CRH_MODE9 
	               | GPIO_CRH_MODE10;
	GPIOA->CRH &= ~ (GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1;
	
	//LED1->PE5 LED0->PB5
	GPIOE->CRL |= GPIO_CRL_MODE5;//最大输出速度为50MHz
	 GPIOE->CRL &= ~GPIO_CRL_CNF5;//推挽(Push-Pull)
	  GPIOB->CRL |= GPIO_CRL_MODE5;//最大输出速度为50MHz
	   GPIOB->CRL &= ~GPIO_CRL_CNF5;//推挽(Push-Pull)	
	
	//LCD_BL PB0
	  GPIOB->CRL |= GPIO_CRL_MODE0;//最大输出速度为50MHz
	   GPIOB->CRL &= ~GPIO_CRL_CNF0;//推挽(Push-Pull)	
	
	//FSMC_GPIO_INIT
	//PE7->D4
	GPIOE->CRL |= GPIO_CRL_MODE7;
	GPIOE->CRL &= ~GPIO_CRL_CNF7;
	GPIOE->CRL |= GPIO_CRL_CNF7_1; 	
	
	//PE8->PE15(D4-D12) ->50MHZ
	GPIOE->CRH |=  GPIO_CRH_MODE8   
								 |GPIO_CRH_MODE9   
								  |GPIO_CRH_MODE10  
								   |GPIO_CRH_MODE11  
								    |GPIO_CRH_MODE12  
								     |GPIO_CRH_MODE13  
								      |GPIO_CRH_MODE14  
								       |GPIO_CRH_MODE15 ;
	//复用推挽
  GPIOE->CRH &= ~(GPIO_CRH_CNF8  |  
								   GPIO_CRH_CNF9  |  
								    GPIO_CRH_CNF10 |  
								     GPIO_CRH_CNF11 |  
								      GPIO_CRH_CNF12 |  
								       GPIO_CRH_CNF13 |  
								        GPIO_CRH_CNF14 |  
								         GPIO_CRH_CNF15);
  GPIOE->CRH |=  GPIO_CRH_CNF8_1 |  
								   GPIO_CRH_CNF9_1 |  
								    GPIO_CRH_CNF10_1 | 
								     GPIO_CRH_CNF11_1 | 
								      GPIO_CRH_CNF12_1 | 
								       GPIO_CRH_CNF13_1 | 
								        GPIO_CRH_CNF14_1 | 
								         GPIO_CRH_CNF15_1 ;
 //PD0-PD1(D2,D3) , PD4-PD5(RW+WE),PD8-PD9-PD10(D13,D14,D15),PD14-PD15(D0-D1)
 
 GPIOD->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 |  
                GPIO_CRL_MODE4 | GPIO_CRL_MODE5 ;
								
 GPIOD->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | 
                  GPIO_CRL_CNF4 | GPIO_CRL_CNF5) ;
									
 GPIOD->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1| 
                GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1;
 
 
 
 GPIOD->CRH |= GPIO_CRH_MODE8  | 
                GPIO_CRH_MODE9  |  
							   GPIO_CRH_MODE10 | 
								  GPIO_CRH_MODE14 |  
							     GPIO_CRH_MODE15 ;  
								 
 GPIOD->CRH &= ~( GPIO_CRH_CNF8| 
                   GPIO_CRH_CNF9|
									  GPIO_CRH_CNF10|
                     GPIO_CRH_CNF14|
										  GPIO_CRH_CNF15); 
								 
 GPIOD->CRH |= GPIO_CRH_CNF8_1 
							| GPIO_CRH_CNF9_1 
							 | GPIO_CRH_CNF10_1
							  | GPIO_CRH_CNF14_1 
							   | GPIO_CRH_CNF15_1 ; 
								 
 //PG12(NE4=CS4),PG0(A10=RS);								 
 GPIOG->CRL |= GPIO_CRL_MODE0;
 GPIOG->CRL &= ~GPIO_CRL_CNF0;
 GPIOG->CRL |= GPIO_CRL_CNF0_1;

 GPIOG->CRH |= GPIO_CRH_MODE12;
 GPIOG->CRH &= ~GPIO_CRH_CNF12;
 GPIOG->CRH |= GPIO_CRH_CNF12_1; 



//gpioc->init
 GPIOC->CRL |= GPIO_CRL_MODE0|
							 GPIO_CRL_MODE1|
							 GPIO_CRL_MODE2|
							 GPIO_CRL_MODE3|
							 GPIO_CRL_MODE4
							 ;
						 
 GPIOC->CRL &=~ (GPIO_CRL_CNF0 |
                 GPIO_CRL_CNF1 |
								 GPIO_CRL_CNF2 |
								 GPIO_CRL_CNF3 |
								 GPIO_CRL_CNF4
                  ); 
}
