#include "stm32f10x.h"
#include "Stm32f10xGpioInit.h"
#include "delay.h"
#include "WST7567.H"
#include "gImage_test.h" 
#include "ASCII_FONT.h"
int main()
{
	Stm32f10xGpioInit(  );
   init_WST7567( );
 
 
 	  printLCD12864(gImage_cc);
	
	
	 print_ASCII8X5('A',3,40 );
	
	 Print_ASCII_Str("abch123FSDF",5,10);
	while(1);
}
