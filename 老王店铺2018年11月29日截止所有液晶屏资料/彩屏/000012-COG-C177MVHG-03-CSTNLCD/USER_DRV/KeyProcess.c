#include "project_config.h"
#define KeyPad_Port GPIOC->IDR;//GPIOC.IDR0->GPIOC.IDR7
//#define Key7    *((uint32_t *) (( GPIOC_BASE +0x08-0x40000000 )*32+7*4+0x42000000))  //GPIOc_iOR bit7 add
//;;;
//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
typedef enum { 
								 normal,   
								 up,
								 down,
								 left,
								 right,
								 center
           }key;


volatile uint8_t Keypad=0;

//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●● 
void InitKeyPort(void)//+C->Filter
{
	GPIOC->CRL &= 0X0000FFFF;//上啦输入
	GPIOC->CRL |= GPIO_CRL_CNF4_1|GPIO_CRL_CNF5_1|GPIO_CRL_CNF6_1|GPIO_CRL_CNF7_1;
	GPIOC->ODR |= 0X00F0 ;//使能上啦
}	          

void ScanKey1(void)
{
volatile 	static uint8_t NewStatus=0,//读键盘最新状态
		                     LastStatus=0,//键盘最后状态
	                       trigger=0;//触发
                          
  NewStatus = KeyPad_Port ;//读键盘
   NewStatus = (NewStatus >>4) ^ 0x0f  ;//保留键盘有效位并取反(键值取反后是1.2.4.8)

   trigger = NewStatus & (NewStatus ^LastStatus);
    LastStatus = NewStatus ;//保留键盘有效位并取反(键值取反后是1.2.4.8)
    switch (trigger)
		{
			case 0:  
		          break ;
			default: Keypad = LastStatus;
		          break ;
	 }
}


//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
void ScanKey(void)
{
volatile 	static uint8_t NewStatus=0,//读键盘最新状态
		                     LastStatus=0,//键盘最后状态
	                       trigger=0 ;//触发
  NewStatus = KeyPad_Port ;//读键盘
  NewStatus = (NewStatus >>4) ^ 0x0f  ;//保留键盘有效位并取反(键值取反后是1.2.4.8)
 
switch(trigger)
{
	case 0:  if(NewStatus != 0)  
	         trigger++;
	         LastStatus = NewStatus ;
		       break ;	

  case 1:  if(LastStatus == NewStatus) 
		          Keypad = LastStatus;
	         else 
					 {
					   trigger=0;
						 break ;
					 } 
					 trigger++;
		       break ;
					 
	case 2:  if(NewStatus == 0) 
	               {
		               LastStatus =0;
		               trigger=0;
								 }
		       break ;

 default: 
		       break ;

}
  
}
//●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
