#include "Stm32F10xUart_init.h"
//异步模式RS232
/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
/* #define SystemCLOCK  24000000 */ 
/* #define SystemCLOCK  36000000 */
/* #define SystemCLOCK  48000000 */
/* #define SystemCLOCK  56000000 */
/* #define SystemCLOCK  72000000

//   #define Baud_RateSet 9600*/
	 
void Stm32f10xUartInit(uint32_t SystemCLOCK,uint32_t Baud_RateSet)
{
	float Fraction =0;
	unsigned int Mantissa=0;
//	 //PA9+PA10 uart1复用推挽模式
//  GPIOA->CRH |= GPIO_CRH_MODE9 
//	               | GPIO_CRH_MODE10;
//	GPIOA->CRH &= ~ (GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
//	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1;
	RCC->APB2ENR |=RCC_APB2ENR_USART1EN;/*!< USART1 clock enable */
	USART1->CR1 |= USART_CR1_UE;/*!< USART Enable */
	USART1->CR1 &=~USART_CR1_M; //0：一个起始位，8个数据位，n个停止位；
//	USART1->CR3 |= 	USART_CR3_DMAT;	/*!< DMA Enable Transmitter */
//	USART1->CR3 |= 	USART_CR3_DMAR; /*!< DMA Enable Receiver */	
	  
	Mantissa  = SystemCLOCK/(Baud_RateSet * 16);
	Fraction =((float)SystemCLOCK/(Baud_RateSet * 16)- Mantissa+0.5)*16;
	USART1->BRR = (Mantissa << 4)+ Fraction;
	USART1->CR1 |= USART_CR1_TE; /*!< Transmitter Enable */
}

void USART1_TX1BYTE(unsigned char data)
{
    while(!( USART1->SR & USART_SR_TXE));
	  USART1->DR = data;
	 
}

void printf_Str( void * str)
{
	uint8_t * str_temp =(uint8_t *) str ;
	while(*str_temp)
	{
		 while(!( USART1->SR & USART_SR_TXE));
	  USART1->DR  = *str_temp;
		str_temp++;
	}
USART1_TX1BYTE('\r');
USART1_TX1BYTE('\n');	
	
}
