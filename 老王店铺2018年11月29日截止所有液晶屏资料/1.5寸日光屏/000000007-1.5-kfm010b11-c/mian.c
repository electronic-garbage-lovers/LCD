
#include "configALL.H"
#include "kfm010b11.H"
#include "gImage_test.h"
#include "ASCII_FONT16x8.h"
#include "GB16x16Font.h"
#include "ASCII_FONT8x8.h"
#include "ASCII_FONT_H16x8.H"
int main(void)
{
//unsigned char COUNT=0;
//unsigned char  count=0;
	//INIT_ALL
	SysTickInit( );
	 Stm32f10xGpio_Init( );
	  Stm32F10x_FsmcInit( );
	   Stm32f10xUartInit(72000000,115200 );
	    init_kfm010b11( ); 
 
  	      

//	LED0 =0;
//	LED1 =1;
//	 
//   Print_a_Ascii8x8('A',0,0);
//	 Print_a_Ascii8x16('A',0,1); 	
	
	
	PrintLcd96x64(gImage_9664); 
  Print_Str_Ascii8x8("https://shop154838422.taobao.com",0,0);
  Print_Str_Ascii8x16("0123456789Ab",3,0) ;
	
 
		 while(1)
		 {
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		 }
}
