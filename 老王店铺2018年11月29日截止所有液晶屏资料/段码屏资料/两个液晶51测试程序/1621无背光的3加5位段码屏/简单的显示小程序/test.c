/*
3+5无背光段码屏

STC15F2K40S2 LQFP44 11.0592MHz 条件下测试 PASS
程序运行了一夜，正常，稳定

2018/7/25

*/

#define WEI 11

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

//D1201控制位（液晶模块接口定义，根据自已的需要更改）
sbit D1201_DAT=P3^5;
sbit D1201_CS=P3^2;     //lower enable
sbit D1201_WR=P3^4;     //rising edge
sbit D1201_RD=P3^3;

#include "LCD-1621.c"     //3+5位段式液晶无背光 0.5元 LCD-V5.3 5v供电效果最好
//#include "DelayMs_15F104E6.h"    //15F104 6M延时

sfr P3M0        =   0xB2;   //0000,0000 端口3模式寄存器0






/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned int t)
{
while(--t)
{
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
}

}








/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{

unsigned int n,m;


//IO口用不用PP模式无所谓，用的时候，屏可以不用接VCC了
//P3M0=0xF0;   

D1621_Init();
cls();



while(1)
{

n++;
print(1,n%1000/100,0);
print(2,n%100/10,0);
print(3,n%10,0);
DelayMs(50);

m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);

}
}

