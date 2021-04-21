#ifndef _KFM010B11_
#define _KFM010B11_
#include "stm32f10x.h"
#include "delay.h"
 
#include "ASCII_FONT8x8.h"
#include "ASCII_FONT_H16x8.H"
void init_kfm010b11(void);//CD初始化


//清屏 
void clear_lcd_kfm010b11(void);


//0输出96X64图
void PrintLcd96x64(const unsigned char *bpm); 


//1●●●●●●输出一个字符宽6高8 一行96/6=16个字符,0-7行LINE
//Print_a_Ascii8x8('A',0,0);
void Print_a_Ascii8x8(unsigned char Ascii,unsigned char line,unsigned char Number);
//1a●●●●●●输出串字符 一行96/6=16个字符,0-7行LINE
//  Print_Str_Ascii8x8("1234567890abcdef",3,0);
void Print_Str_Ascii8x8(void *StrAscii,unsigned char line,unsigned char Number);



//2●●●●●●输出一个字符宽8x高16 一行96/8=12个字符,0-3行LINE
//Print_a_Ascii8x16('A',0,0);
void Print_a_Ascii8x16(unsigned char Ascii,unsigned char line,unsigned char Number);
//22●●●●●●输出一个字符 一行96/8=12个字符,0-3行LINE
//	Print_Str_Ascii8x16("0123456789Ab",2,0) ;
void Print_Str_Ascii8x16(void *StrAscii,unsigned char line,unsigned char Number);



////●●●●●●开窗口显示,X(0-7Page,1Page=1BYTE),Y(0->95)
////  Display_windows(gImage_48x48, 1,7,0,48);	
//void Display_windows(const unsigned char * DotData, unsigned char StartX,unsigned char EndX,unsigned char StartY,unsigned char EndY);


//位置测试
//void test_sendByte(unsigned char x,unsigned char y ); 
#endif








