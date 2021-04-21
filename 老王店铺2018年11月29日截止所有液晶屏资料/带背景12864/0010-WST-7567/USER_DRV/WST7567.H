#ifndef _WST7567_H_
#define _WST7567_H_
#include "stm32f10x.h"
#include "delay.h"
#include "ASCII_FONT.h"
void init_WST7567(void);//CD初始化
void WST7567_CLS(unsigned char CLS_Data);//LCD清屏
void printLCD12864( const void *  data); //LCD全屏输出一图片



//LCD输出一个ASCII字符--->参数(ASCII字符,页(0-7),开始列(0-127))
void print_ASCII8X5(unsigned char ASCII,unsigned char Page,unsigned char Column );
//LCD输出窜ASCII字符窜--->参数(ASCII字符窜,页(0-7),开始列(0-127))
void Print_ASCII_Str(void const* ASCI_str,unsigned char Page,unsigned char Column);
#endif
