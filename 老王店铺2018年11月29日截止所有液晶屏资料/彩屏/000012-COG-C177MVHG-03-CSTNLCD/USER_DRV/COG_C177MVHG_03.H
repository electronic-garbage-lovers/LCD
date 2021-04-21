#ifndef _COG_C177MVHG_03_H_
#define _COG_C177MVHG_03_H_
#include "stm32f10x.h"
#include "delay.h"
#include "ASCII_FONT_V8x8.h"
#include "ASCII_FONT_V8X16.h"
/*------RGB color definitions------------------------*/
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F
/*------LCD初始化---------*/ 		
void Init_COG_C177MVHG_03_H(void); 
/*------LCD写指令---------*/
void  LCDWriteCommand(unsigned char command); 
/*------LCD写数据---------*/
void  LCDWriteData(unsigned int Dot_Data); 
/*------全屏刷图128x160 ---------*/
void Display128x160glmage( const void  * DotDATA); 
/*------清屏---------*/
void ClsLCD(unsigned int clsdata); 
/*------设置XY坐标，画点(//横屏模式160x120，第一象限X(0->128),Y->0-159)---------*/
void DrawDot(unsigned char X,unsigned char Y,unsigned int DotColor); 
/*------画点---------*/
//●        Y(0-127)
//画点160X128 |  
//X->(0-127) |
//Y->(0-159) |_______________X(0-159)
//坐标在第一象限 
//void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor)
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor);
/*------在指定位置画一个指定大小的空心圆---------*/
//●在指定位置画一个指定大小的空心圆00
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,unsigned int DotColor);
/*-----画矩形---------*/
//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor);

//输出一个ASCII字符，X=160/8=20(0->19),Y=128/16=8(0->),横屏模式
void LcdPrint1Ascii8X16(unsigned char ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor);

//输出8X16ASCII字符串，X=160/8=20(0->19),Y=128/16=8(0->7),横屏模式
void LcdPrint1AsciiStr8X16(const void * ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor);
#endif
