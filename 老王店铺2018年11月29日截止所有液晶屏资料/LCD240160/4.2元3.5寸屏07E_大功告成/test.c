/* 
3.5寸 240160 32灰度屏

F8x16

感谢晓熊QQ 的引脚定义和初始代码

2018-11-14
*/
#include <reg52.H>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int


sbit lcd_rs=P1^1; 
sbit lcd_en=P1^2;
sbit lcd_wr=P1^3; 
sbit lcd_reset=P1^4;
sbit lcd_cs1=P1^0; 

#define DataPort P0   //DataBUS

#include "8x16.h"

/*延时：1 毫秒的i 倍*/
void delay(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<110;k++);
}
/*延时：1us 的i 倍*/
void delay_us(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<2;k++);
}

//并口方式
//写指令到LCD 模块
void transfer_command_lcd(int data1)
{
lcd_rs=0;
lcd_en=1;
P0=data1;
lcd_en=0;
}

//写数据到LCD 模块
void transfer_data_lcd(int data1)
{
lcd_rs=1;
lcd_en=1;
P0=data1;
lcd_en=0;
}


void initial_lcd()
{
lcd_wr=0;   //0 写  1读
lcd_cs1=0;  //cs 0有效
lcd_reset=0; //rst
delay(50);
lcd_reset=1;
delay(50);

 
transfer_command_lcd(0x30); //EXT=0 
transfer_command_lcd(0x94); //Sleep out 
transfer_command_lcd(0x31); //EXT=1 
transfer_command_lcd(0xD7); //Autoread disable 
transfer_data_lcd(0X9F); // 
transfer_command_lcd(0x32); //Analog SET 
transfer_data_lcd(0x00); //OSC Frequency adjustment 
transfer_data_lcd(0x01); //Frequency on booster capacitors->6KHz 
transfer_data_lcd(0x03); //Bias=1/13 
transfer_command_lcd(0x20); //灰度设置 
transfer_data_lcd(0x01); 
transfer_data_lcd(0x03); 
transfer_data_lcd(0x05); 
transfer_data_lcd(0x07); 
transfer_data_lcd(0x09); 
transfer_data_lcd(0x0b); 
transfer_data_lcd(0x0d); 
transfer_data_lcd(0x10); 
transfer_data_lcd(0x11); 
transfer_data_lcd(0x13); 
transfer_data_lcd(0x15); 
transfer_data_lcd(0x17); 
transfer_data_lcd(0x19); 
transfer_data_lcd(0x1b); 
transfer_data_lcd(0x1d); 
transfer_data_lcd(0x1f); 
transfer_command_lcd(0x30); //EXT1=0，EXT0=0,表示选择了“扩展指令表 1” 
transfer_command_lcd(0x75); //页地址设置 
transfer_data_lcd(0X00); //起始页地址：YS=0X00 
transfer_data_lcd(0X14); //结束页地址：YE=0x1F每 4 行为一页，第 0～3 行为第 0 页，第 124～127 行为第 31 页（31=0x1f） 

transfer_command_lcd(0x15); //列地址设置 
transfer_data_lcd(0X00); //起始列地址：XS=0 
transfer_data_lcd(0Xef); //结束列地址：XE=240（0xef） 
transfer_command_lcd(0xbc); //行列扫描方向 
transfer_data_lcd(0x02); //MX.MY=Normal 
// transfer_command_lcd(0x0c); //数据格式选择,0x0C 是低位在前 D0-D7,0x08 是高位在前 D7-D0 
transfer_command_lcd(0xCA); //显示控制 
transfer_data_lcd(0X00); //设置 CL 驱动频率：CLD=0 
transfer_data_lcd(0X9F); //占空比：Duty=160 
transfer_data_lcd(0X20); //N 行反显：Nline=off 
transfer_command_lcd(0xF0); //显示模式 
transfer_data_lcd(159); //如果设为 0x11：表示选择 4 灰度级模式，如果设为 0x10:表示选择黑白模式 
transfer_command_lcd(0x81); //设置对比度，“0x81”不可改动，紧跟着的 2 个数据是可改的，但“先微调后粗调”这 
transfer_data_lcd(0xA0);  //微调对比度,可调范围 0x00～0x3f，共 64 级 0
transfer_data_lcd(0x03); //粗调对比度,可调范围 0x00～0x07，共 8 级 
transfer_command_lcd(0x20); //电源控制 
transfer_data_lcd(0x0B); //D0=regulator ; D1=follower ; D3=booste, on:1 off:0 
delay_us(100); 
transfer_command_lcd(0xAF); //打开显示 

}









unsigned int encode(unsigned char d1,unsigned char d2, unsigned char d3)
{
return (d3<<11)+(d2<<6) +d1 ;
}





#define STC90C
#include "uart2017.c"

void printf_num(unsigned char x)
{
Com_SendByte(0x30+x/100);
Com_SendByte(0x30+x%100/10);
Com_SendByte(0x30+x%10);
Com_SendByte(' ');
}


void locate(unsigned char x, unsigned char y)
{
x+=24;
y=159-y;
transfer_command_lcd(x&0x0f);
transfer_command_lcd(0x10|(x>>4));
transfer_command_lcd(0x60+(y&0x0f));
transfer_command_lcd(0x70+(y>>4));
}



void cls(unsigned int c)
{
unsigned char y,j;
for(y=0;y<160;y++)
 {
  locate(0,y);
  for(j=0;j<80;j++)
   {
    transfer_data_lcd(c>>8);
    transfer_data_lcd(c);
   }
 }
}






void printf_c(unsigned char x, unsigned char y,unsigned char c,unsigned char gray)
{
unsigned char i;         //循环变量
unsigned char temp;      //暂存字模
unsigned char d1,d2,d3;  //准备编码的三个点
unsigned int lcddata;    //准备写到液晶的数据
for(i=0;i<16;i++)
 {
  locate(x,y+i);
  temp=Font8x16[c][i];
  printf_num(temp); //串口打印字模代码

  d1=0;d2=0;d3=0;
  if(temp&0x80) d1=gray;  
  if(temp&0x40) d2=gray;  
  if(temp&0x20) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=0;d2=0;d3=0;
  if(temp&0x10) d1=gray;  
  if(temp&0x08) d2=gray;  
  if(temp&0x04) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=0;d2=0;
  if(temp&0x02) d1=gray;  
  if(temp&0x01) d2=gray;  
  lcddata=encode(d1,d2,0);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   
  
 }

}

void printf(unsigned char x, unsigned char y, unsigned char *s,unsigned char gray)
{
while(*s)
 {
  printf_c(x,y,*s,gray);
  s++;
  x+=3;
 }
}

/*---------------------
   画横线   x2是长度
---------------------*/
void line(unsigned char x, unsigned char y, unsigned char x2, unsigned char gray)
{
locate(x,y);
x2/=3;
while(x2--)
 {
  transfer_data_lcd(encode(gray,gray,gray)>>8);
  transfer_data_lcd(encode(gray,gray,gray));
 }

}

void main()
{
unsigned char i;
delay(100);
InitUART();
SendStr("\r\n\r\nLCD TEST.\r\n\r\n");

initial_lcd(); //对液晶模块进行初始化设置

cls(0x0000);
printf(0,0," * LCD 240x160 TEXT Demo *",31);
printf(6,40,"ABCDEFG abcdefg",31);
printf(6,60,"1234567890+-*\.<>[];'|",31);
printf(6,80,"Gray Level 0<-->31",31);
printf(20,140,"2018-11-14",31);
line(0,20,240,20);
line(0,22,240,20);
for(i=0;i<16;i++)
 printf_c(5+i*4,100,'*',i);
for(;i<32;i++)
 printf_c(5+(i-16)*4,120,'*',i);

while(1);


}



