/* 

*/
#include <reg52.H>
#include <intrins.h>

//////////////// LCD IO ////////////////
sbit lcd_cs=P2^4;   //Ƭѡ
sbit lcd_rs=P2^3;    //�������
sbit lcd_en=P2^2;    //ʱ��
sbit lcd_wr=P2^1;    //�� or д
sbit lcd_reset=P2^0; //RESET
#define DataPort P0  //����
////////////// FLASH ///////////////////
sbit FLASH_CS=P1^4;

#include "spi.c"
#include "lcd240160.c"     //LCD 240*160 ��������
#include "lcd_printf.c"    //�ַ���ӡ



void readme()
{
cls(0x0000);
printf(1,2,"Һ���������Լ�����������",31,0);
line(0,22,240,31);
printf(1,30,"1 D7  2 D6  3 D5  4 D4",31,0);
printf(1,50,"5 D3  6 D2  7 D1  8 D0",31,0);
printf(1,70,"9 RST 10WR  11RD  12A0",31,0);
printf(1,90,"13CS  14GND 15VCC 16�Ƹ���",31,0);
printf(1,110,"17�������  18�׵�����",31,0);
line(0,132,240,31);
printf(1,140,"��ʼ���������ST75256",31,0);

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
printf(10,15,"��ʮ�������Ⱥڰ���ʾ",31,0);
printf(13,130,"�� <---------> ��",31,0);
delay(60000);
}



/*------------------
      M A I N
-------------------*/
void main()
{
unsigned char i;

InitSPI();
initial_lcd(); //��Һ��ģ����г�ʼ������

while(1)
{
cls(0x0000);
printf(0,0,"* LCD 240*160 32���Ҷ��� *",31,0);
printf(6,40,"��Ӣ���ַ���ͼ�β���",31,0);
printf(6,60,"��Ƭ����STC12C5a60s2",31,0);
printf(6,80,"�Ҷȼ��� 0<---->31",31,0);
printf(24,140,"2018-11-15 ��10��",31,0);
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



