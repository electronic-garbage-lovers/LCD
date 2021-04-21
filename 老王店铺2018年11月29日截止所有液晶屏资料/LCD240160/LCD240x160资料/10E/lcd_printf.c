/*
LCD 240 x 160 专用打印程序
uc1698u 原是160x128xrgb CSTN驱动芯片
现在用于点阵屏，rgb被分别控制三个点的灰度
也就是说，一次需要写16位数据，一个16位数据
控制3个连续点的灰度，本程序和之前点阵屏的
区别在于，要对字模数据先解码，然后再重新用
灰度值进行编码。

2018-11-15
by 晴窗伴侣
*/

#include "8x16.h"  //8x16英文字模 从0x20开始
#include "W25X.h"

/*------------------
打印一个8x16的英文
字模在程序中
-------------------*/
void printf_c(unsigned char x, unsigned char y,unsigned char c,unsigned char gray,unsigned char bg)
{
unsigned char i;        
unsigned char temp;     
unsigned char d1,d2,d3;
unsigned int lcddata;   
c-=' ';
for(i=0;i<16;i++)
 {
  locate(x,y+i);
  temp=Font8x16[c][i];

  d1=bg;d2=bg;d3=bg;
  if(temp&0x80) d1=gray;  
  if(temp&0x40) d2=gray;  
  if(temp&0x20) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x10) d1=gray;  
  if(temp&0x08) d2=gray;  
  if(temp&0x04) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x02) d1=gray;  
  if(temp&0x01) d2=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   
  
 }
}




void printf_hz(unsigned char x, unsigned char y,unsigned char c[2],unsigned char gray,unsigned char bg)
{
unsigned char i;
unsigned long int Dst_Addr;
unsigned char d1,d2,d3,temp; //三个点的数据和读到的字模
unsigned int lcddata;       //准备写屏的数据

 Dst_Addr=(long)( (c[0]-161)*94 + (c[1]-161) ) * 32 + 4096;
 FLASH_CS = 0;     /* enable device */
 SPI_RW(W25P_FastReadData);   /* read command */
 SPI_RW(((Dst_Addr & 0xFFFFFF) >> 16));  /* send 3 address bytes */
 SPI_RW(((Dst_Addr & 0xFFFF) >> 8));
 SPI_RW(Dst_Addr & 0xFF);
 SPI_RW(0xFF);   /*dummy byte*/
 for(i=0;i<16;i++)
 {
  locate(x,y+i);       //一行18个点, 第1和18点不写

  temp=SPI_RW(0xFF); 
  d1=bg;d2=bg;d3=bg;
  if(temp&0x80) d2=gray;  
  if(temp&0x40) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x20) d1=gray;  
  if(temp&0x10) d2=gray;  
  if(temp&0x08) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x04) d1=gray;  
  if(temp&0x02) d2=gray;  
  if(temp&0x01) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  temp=SPI_RW(0xFF); 
  d1=bg;d2=bg;d3=bg;
  if(temp&0x80) d1=gray;  
  if(temp&0x40) d2=gray;  
  if(temp&0x20) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x10) d1=gray;  
  if(temp&0x08) d2=gray;  
  if(temp&0x04) d3=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   

  d1=bg;d2=bg;d3=bg;
  if(temp&0x02) d1=gray;  
  if(temp&0x01) d2=gray;  
  lcddata=encode(d1,d2,d3);
  transfer_data_lcd(lcddata>>8);   
  transfer_data_lcd(lcddata);   
 }

 FLASH_CS = 1; 
}









/*---------------------------
        打印字符串
----------------------------*/
void printf(unsigned char x, unsigned char y, unsigned char *s,unsigned char gray,unsigned char bg)
{
while(*s)
 {
  if(*s<0x80)
  {
   printf_c(x,y,*s,gray,bg);
   s++;
   x+=3;
  }
  else
  {
   printf_hz(x,y,(unsigned char*)s,gray,bg);
   s+=2;
   x+=6;
  }

 }
}

/*---------------------
   画模线 x2是长度
---------------------*/
void line(unsigned char x, unsigned char y, unsigned char x2, unsigned char gray)
{
unsigned int temph,templ;
locate(x,y);
x2/=3;
temph=encode(gray,gray,gray)>>8;
templ=encode(gray,gray,gray);
while(x2--)
 {
  transfer_data_lcd(temph);
  transfer_data_lcd(templ);
 }

}