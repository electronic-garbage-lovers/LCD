/*
无背光段码屏， 1621驱动

2018-7-25 晴窗伴侣
*/
// 测试哪一个位置，这个屏的位置是0,2,4 11,13,15,17，第4位的那个米字型点了678910共5个4bit  20bit
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
unsigned char i;
unsigned char d;


//P3M0=0xF0;

D1621_Init();  //安始化

cls();  //清屏

while(1)
{
d=1;  //段码 00000001 (B)

D1201_CS=0;  //CS有效

for(i=0;i<8;i++)
{

 D1201_CS=0;

 D1201WrDataCmd(WEI);//准备写入的位置
 SENTDATA(d); //写入的数据，也就是段码

 D1201_CS=1;  //CS无效，放开总线

 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);

 d<<=1;  //改变一下段码，这个不解释了，需要有一定的51基础和C基础

}

}







}

