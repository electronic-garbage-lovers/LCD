/*
YXD-1621TZ01

2018/7/24
*/

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

//D1201控制位（液晶模块接口定义，根据自已的需要更改）
sbit D1201_DAT=P3^5;
sbit D1201_CS=P3^2;     //lower enable
sbit D1201_WR=P3^4;     //rising edge
sbit D1201_RD=P3^3;

#include "YXD-1621.c"     //12位段式液晶
//#include "DelayMs_15F104E6.h"    //15F104 6M延时


sbit LEDA=P3^6;
sbit LEDK=P3^7;


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

sfr P3M0        =   0xB2;   //0000,0000 端口3模式寄存器0











/*------------------------------------------------
          初始化定时器1,用于扫描数码管
------------------------------------------------*/
void Init_Timer1(void)    //使用定时器1扫描数码管
{
 TMOD |= 0x10;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响 
 TH1=0x00;	      //给定初值，这里使用定时器最大值从0开始计数一直到65535溢出
 TL1=0x00;
 EA=1;            //总中断打开
 ET1=1;           //定时器中断打开
 TR1=1;           //定时器开关打开
}




unsigned char speed,speed2;

/*------------------------------------------------
                 定时器中断子程序 1
				    数码管扫描
------------------------------------------------*/
void Timer1_isr(void) interrupt 3 using 1
{
   TH1=0xFF;                 //FE0B为 [200/6]Hz 扫描频率
   TL1=0x0B;
   speed++;
   if(speed==speed2) speed=0;
   if(speed==0)
    LEDA=1;
	else
	LEDA=0;
}






/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned char i;

speed2=3;
P3M0=0x40;  //PP 3.6
Init_Timer1();

LEDK=0;

//unsigned char d;

D1201_Init();

/*
while(1)
{
d=1;
 D1201_CS=0;
 D1201WrDataCmd(0);//往RAM的地址4写数据?这里的参数范围为:0-31
 SENTDATA(0);
 D1201_CS=1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);


for(i=0;i<8;i++)
{
 D1201_CS=0;
 D1201WrDataCmd(0);//往RAM的地址4写数据?这里的参数范围为:0-31
 SENTDATA(d);
 D1201_CS=1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 d<<=1;
}

}

*/




cls();
i=1;

while(1)
{



print( i,i%16,0);   
DelayMs(50);

print( i,i%16,1);   
DelayMs(50);


print( i,21,0);  
DelayMs(50);

i++;
if(i==17) 
{
for(i=1;i<17;i++)
 print(i,i%16,1);
DelayMs(1000);
DelayMs(250);
for(i=1;i<17;i++)
 print(i,21,0);
DelayMs(1000);
for(i=1;i<17;i++)
 print(i,i%16,1);
DelayMs(30000);

i=1;
}




}
}

