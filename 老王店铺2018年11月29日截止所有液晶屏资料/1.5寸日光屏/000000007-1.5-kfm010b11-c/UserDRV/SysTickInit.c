#include "SysTickInit.h"
 
//●●●●●●●●●●●●●●●●●●●●●●●●
/*01系统时钟选择*/ 
/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
/* #define SystemCLOCK  24000000 */ 
/* #define SystemCLOCK  36000000 */
/* #define SystemCLOCK  48000000 */
/* #define SystemCLOCK  56000000 */
   #define SystemCLOCK  72000000
	 
/*02使用中断方式选择,定义SysTick_Use_interrupt_Mode*/
//#define SysTick_Use_interrupt_Mode
//●●●●●●●●●●●●●●●●●●●●●●●●



#ifdef 	SysTick_Use_interrupt_Mode 
//●中断方式1
static volatile  uint32_t delayTime =0;

void SysTickInit(void)
{
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick 定时器的cls使能位
	SysTick->CTRL |= 1ul << 2 ;//1=内核时钟不分频(FCLK)
	SysTick->VAL =0x00000000;//写任意数清零
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;//使能中断
}

void SysTick_Handler(void)
{
	
	if( delayTime   )
			delayTime --;
}
//毫秒延时
void SysTickDelay1MS(uint32_t delayNms)
{
	delayTime = delayNms;
	SysTick->LOAD = SystemCLOCK / 1000;//1MS
	SysTick->CTRL |=SysTick_CTRL_ENABLE;
	while(delayTime);
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick 定时器的cls使能位
	SysTick->VAL =0x00000000;//写任意数清零
}
//毫秒延时
void SysTickDelay1Us(uint32_t delayNus)
{
	delayTime = delayNus;
	SysTick->LOAD = SystemCLOCK / 1000000;//1uS
	SysTick->CTRL |=SysTick_CTRL_ENABLE;
	while(delayTime);
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick 定时器的cls使能位
	SysTick->VAL =0x00000000;//写任意数清零
}



#else 
//●查询方式2
void SysTickInit(void)
{
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;//Set CLK=Cpu.Clcok
	SysTick->VAL  = 0x00000000ul;           //SysTick计数寄存奇清零
	
}
//毫秒延时
void SysTickDelay1MS(uint32_t delayNms)
{
	SysTick->LOAD = SystemCLOCK /1000 ;//设置位1MS
	SysTick->CTRL |= SysTick_CTRL_ENABLE;/*!< Counter enable */
	while(delayNms)
	{
		if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
		{	 
			delayNms--;
		}
	}
 SysTick->CTRL &= ~SysTick_CTRL_ENABLE;	/*!< Counter Disable */
	SysTick->VAL  = 0x00000000ul;   //SysTick计数寄存奇清零
}

//微秒延时
void SysTickDelay1Us(uint32_t delayNus)
{
	SysTick->LOAD = SystemCLOCK /1000000 ;//设置位1uS
	SysTick->CTRL |= SysTick_CTRL_ENABLE;/*!< Counter enable */
	while(delayNus)
	{
		if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
		{	 
			delayNus--;
		}
	}
 SysTick->CTRL &= ~SysTick_CTRL_ENABLE;	/*!< Counter Disable */
	SysTick->VAL  = 0x00000000ul;   //SysTick计数寄存奇清零
}

#endif


#ifdef SystemCLOCK
#undef  SystemCLOCK
#endif
