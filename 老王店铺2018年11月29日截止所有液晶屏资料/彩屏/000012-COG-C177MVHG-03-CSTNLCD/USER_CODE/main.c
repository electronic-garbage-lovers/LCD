#include "stm32f10x.h"
#include "Stm32f10xGpioInit.h"
#include "delay.h"
#include "gImage_test.h" 
#include "ASCII_FONT_V8x8.h"
#include "ASCII_FONT_V8X16.h"
#include "stm32f10x_AFIO.H"
#include "COG_C177MVHG_03.H"
#include "LED0.H"

 
int main()
{
	Stm32f10xGpioInit( );
   stm32f10x_AFIO( );
   Init_COG_C177MVHG_03_H( );
	
	
 Display128x160glmage(gImage_cc);//全屏刷图128x160 	
// 
//DrawDot(0,0,Red);//设置XY坐标，画点	
//DrawDot(159,0,White);//设置XY坐标，画点	
//DrawDot(0,127,Blue);//设置XY坐标，画点	
//DrawDot(159,127,Green);//设置XY坐标，画点		
//	
// 	
//LCD_DrawLine(0, 0,159, 127,Green)	;
//		delay_1ms(1000);		
//LCD_Draw_Circle(80,64,30,Red);	
//		delay_1ms(1000);		
//LCD_DrawRectangle(00, 00, 64, 80,Blue);	
//			delay_1ms(1000);	
//	
//  LcdPrint1Ascii8X16('0',19,0,Green,Black);
//  LcdPrint1Ascii8X16('0',18,0,Green,Black);
//  LcdPrint1Ascii8X16('0',17,0,Green,Black);	
//  LcdPrint1Ascii8X16('A',1,1,Red,Black);	
//	
//  LcdPrint1Ascii8X16('A',2,2,Blue,Black);		
	//输出8X16ASCII字符串，X=160/8=20(0->19),Y=128/16=8(0->7),横屏模式
 LcdPrint1AsciiStr8X16("Hello !!!",0,0,Green,Black);
 LcdPrint1AsciiStr8X16("ABCDEFGHI",0,1,Red,Black); 
 LcdPrint1AsciiStr8X16("abcdefghi",0,2,Blue,Black);  
// LcdPrint1AsciiStr8X16("01234567890",0,3,Green,Black);
// LcdPrint1AsciiStr8X16("ABCDEFGHI",0,4,Red,Black); 
// LcdPrint1AsciiStr8X16("abcdefghi",0,5,GreenYellow,Black); 
// LcdPrint1AsciiStr8X16("01234567890",0,6,Magenta,Black);
//  LcdPrint1AsciiStr8X16("ABCDEFGHI",0,7,Yellow,Black); 
   
LCD_DrawLine(0, 0,159, 127,Green)	;
		delay_1ms(1000);		
LCD_Draw_Circle(80,64,30,Red);	
		delay_1ms(1000);		
//LCD_DrawRectangle(00, 00, 64, 80,Blue);	
			delay_1ms(1000);	 
	while(1)
	{
 		
//		
//		Display128x160glmage(gImage_cc);//全屏刷图128x160 		
//		delay_1ms(1000);	

//	
//		
//		ClsLCD(0xf800);	

//		delay_1ms(1000);
//		ClsLCD(0x07e0);	
//		delay_1ms(1000);

//		ClsLCD(0x001f);	
//		delay_1ms(1000);


		
    LED0_Negate();		
    delay_1ms(500);		
	}
}
