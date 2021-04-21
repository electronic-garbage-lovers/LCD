/*
LCD 240 x 160 ר�ô�ӡ����
uc1698u ԭ��160x128xrgb CSTN����оƬ
�������ڵ�������rgb���ֱ����������ĻҶ�
Ҳ����˵��һ����Ҫд16λ���ݣ�һ��16λ����
����3��������ĻҶȣ��������֮ǰ��������
�������ڣ�Ҫ����ģ�����Ƚ��룬Ȼ����������
�Ҷ�ֵ���б��롣

2018-11-15
by �細����
*/

#include "8x16.h"  //8x16Ӣ����ģ ��0x20��ʼ
#include "W25X.h"

/*------------------
��ӡһ��8x16��Ӣ��
��ģ�ڳ�����
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
unsigned char d1,d2,d3,temp; //����������ݺͶ�������ģ
unsigned int lcddata;       //׼��д��������

 Dst_Addr=(long)( (c[0]-161)*94 + (c[1]-161) ) * 32 + 4096;
 FLASH_CS = 0;     /* enable device */
 SPI_RW(W25P_FastReadData);   /* read command */
 SPI_RW(((Dst_Addr & 0xFFFFFF) >> 16));  /* send 3 address bytes */
 SPI_RW(((Dst_Addr & 0xFFFF) >> 8));
 SPI_RW(Dst_Addr & 0xFF);
 SPI_RW(0xFF);   /*dummy byte*/
 for(i=0;i<16;i++)
 {
  locate(x,y+i);       //һ��18����, ��1��18�㲻д

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
        ��ӡ�ַ���
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
   ��ģ�� x2�ǳ���
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