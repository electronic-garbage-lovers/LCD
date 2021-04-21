/* 

*/
#include <reg52.H>
#include <intrins.h>

//////////////// LCD IO ////////////////
sbit lcd_cs=P2^4;   //片选
sbit lcd_rs=P2^3;    //命令，数据
sbit lcd_en=P2^2;    //时钟
sbit lcd_wr=P2^1;    //读 or 写
sbit lcd_reset=P2^0; //RESET
#define DataPort P0  //总线
////////////// FLASH ///////////////////
sbit FLASH_CS=P1^4;

#include "spi.c"
#include "lcd240160.c"     //LCD 240*160 驱动程序
#include "lcd_printf.c"    //字符打印



void readme()
{
cls(0x0000);
printf(1,2,"液晶屏面向自己，引脚左起",31,0);
line(0,22,240,31);
printf(1,30,"1 D7  2 D6  3 D5  4 D4",31,0);
printf(1,50,"5 D3  6 D2  7 D1  8 D0",31,0);
printf(1,70,"9 RST 10WR  11RD  12A0",31,0);
printf(1,90,"13CS  14GND 15VCC 16灯负极",31,0);
printf(1,110,"17红灯正极  18白灯正极",31,0);
line(0,132,240,31);
printf(1,140,"初始化代码兼容ST75256",31,0);

delay(60000);
}


void picture()
{
unsigned char y;
unsigned char i;
cls(0x0000);
for(y=50;y<100;y++)
 {
  locate(5,y);
  for(i=0;i<32;i++)
  {
   transfer_data_lcd(encode(i,i,i)>>8);
   transfer_data_lcd(encode(i,i,i));
   transfer_data_lcd(encode(i,i,i)>>8);
   transfer_data_lcd(encode(i,i,i));
  }
 
 }
printf(10,15,"三十二级亮度黑白演示",31,0);
printf(13,130,"暗 <---------> 亮",31,0);
delay(60000);
}



/*------------------
      M A I N
-------------------*/
void main()
{
unsigned char i;

InitSPI();
initial_lcd(); //对液晶模块进行初始化设置

while(1)
{
cls(0x0000);
printf(0,0,"* LCD 240*160 32级灰度屏 *",31,0);
printf(6,40,"中英文字符和图形测试",31,0);
printf(6,60,"单片机：STC12C5a60s2",31,0);
printf(6,80,"灰度级别 0<---->31",31,0);
printf(24,140,"2018-11-15 第10版",31,0);
line(0,20,240,31);
line(0,22,240,31);
for(i=0;i<16;i++)
 printf_c(5+i*4,100,'*',i,0);
for(;i<32;i++)
 printf_c(5+(i-16)*4,120,'*',i,0);
delay(60000);

readme();
picture();


}

}



