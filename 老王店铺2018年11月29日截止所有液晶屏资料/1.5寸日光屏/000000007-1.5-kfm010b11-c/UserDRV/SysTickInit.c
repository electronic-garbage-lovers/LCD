#include "SysTickInit.h"
 
//�������������������������
/*01ϵͳʱ��ѡ��*/ 
/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
/* #define SystemCLOCK  24000000 */ 
/* #define SystemCLOCK  36000000 */
/* #define SystemCLOCK  48000000 */
/* #define SystemCLOCK  56000000 */
   #define SystemCLOCK  72000000
	 
/*02ʹ���жϷ�ʽѡ��,����SysTick_Use_interrupt_Mode*/
//#define SysTick_Use_interrupt_Mode
//�������������������������



#ifdef 	SysTick_Use_interrupt_Mode 
//���жϷ�ʽ1
static volatile  uint32_t delayTime =0;

void SysTickInit(void)
{
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick ��ʱ����clsʹ��λ
	SysTick->CTRL |= 1ul << 2 ;//1=�ں�ʱ�Ӳ���Ƶ(FCLK)
	SysTick->VAL =0x00000000;//д����������
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;//ʹ���ж�
}

void SysTick_Handler(void)
{
	
	if( delayTime   )
			delayTime --;
}
//������ʱ
void SysTickDelay1MS(uint32_t delayNms)
{
	delayTime = delayNms;
	SysTick->LOAD = SystemCLOCK / 1000;//1MS
	SysTick->CTRL |=SysTick_CTRL_ENABLE;
	while(delayTime);
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick ��ʱ����clsʹ��λ
	SysTick->VAL =0x00000000;//д����������
}
//������ʱ
void SysTickDelay1Us(uint32_t delayNus)
{
	delayTime = delayNus;
	SysTick->LOAD = SystemCLOCK / 1000000;//1uS
	SysTick->CTRL |=SysTick_CTRL_ENABLE;
	while(delayTime);
	SysTick->CTRL &=~(1ul << SysTick_CTRL_ENABLE_Pos);//OFF->SysTick ��ʱ����clsʹ��λ
	SysTick->VAL =0x00000000;//д����������
}



#else 
//���ѯ��ʽ2
void SysTickInit(void)
{
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;//Set CLK=Cpu.Clcok
	SysTick->VAL  = 0x00000000ul;           //SysTick�����Ĵ�������
	
}
//������ʱ
void SysTickDelay1MS(uint32_t delayNms)
{
	SysTick->LOAD = SystemCLOCK /1000 ;//����λ1MS
	SysTick->CTRL |= SysTick_CTRL_ENABLE;/*!< Counter enable */
	while(delayNms)
	{
		if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
		{	 
			delayNms--;
		}
	}
 SysTick->CTRL &= ~SysTick_CTRL_ENABLE;	/*!< Counter Disable */
	SysTick->VAL  = 0x00000000ul;   //SysTick�����Ĵ�������
}

//΢����ʱ
void SysTickDelay1Us(uint32_t delayNus)
{
	SysTick->LOAD = SystemCLOCK /1000000 ;//����λ1uS
	SysTick->CTRL |= SysTick_CTRL_ENABLE;/*!< Counter enable */
	while(delayNus)
	{
		if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
		{	 
			delayNus--;
		}
	}
 SysTick->CTRL &= ~SysTick_CTRL_ENABLE;	/*!< Counter Disable */
	SysTick->VAL  = 0x00000000ul;   //SysTick�����Ĵ�������
}

#endif


#ifdef SystemCLOCK
#undef  SystemCLOCK
#endif
