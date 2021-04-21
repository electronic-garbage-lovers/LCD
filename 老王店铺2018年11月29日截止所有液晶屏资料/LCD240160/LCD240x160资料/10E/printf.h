/*------------------------------------
        F L A S H 打印程序

本程序在1.8寸12864SPI上测试通过
汉字库芯片 W25Q08 - W25Q128均可
写入的是12864扫描方式的16x16宋体

2018-10-17
--------------------------------------*/

#include "W25X.h"


// 打一个中文 16x16
void printf_h16(unsigned char x, unsigned char y, unsigned char c[2])
{
unsigned char i;
unsigned long int Dst_Addr;


 Dst_Addr=(long)( (c[0]-161)*94 + (c[1]-161) ) * 32 ;
 FLASH_CS = 0;     /* enable device */
 SPI_RW(W25P_FastReadData);   /* read command */
 SPI_RW(((Dst_Addr & 0xFFFFFF) >> 16));  /* send 3 address bytes */
 SPI_RW(((Dst_Addr & 0xFFFF) >> 8));
 SPI_RW(Dst_Addr & 0xFF);
 SPI_RW(0xFF);   /*dummy byte*/

x+=2;
send2LCM(0,y+0xb0);
send2LCM(0,0x10 | x>>4);
send2LCM(0,x & 0x0f);

for(i=0;i<16;i++) 
 { 
   send2LCM(1,SPI_RW(0xff)); 
 } 

send2LCM(0,y+1+0xb0);
send2LCM(0,0x10 | x>>4);
send2LCM(0,x & 0x0f); 
for(i=0;i<16;i++) 
 { 
   send2LCM(1,SPI_RW(0xff)); 
 } 

 FLASH_CS = 1; 
}



//打高度为16的中英文字符串
void printf_16(unsigned int x, unsigned int y, unsigned char *s) 
{
unsigned char l=0;

	while(*s) 
	 {
		if( *s < 0x80) 
		    {
            if(x+l<=122)  
             {
              printf_c(x+l,y+1,*s);
			  l+=6;s++;
             }
             else
             {
              return;
             }
			}
		else
		    {
            if(x+l<=112) 
             {
              printf_h16(x+l,y,(unsigned char*)s);
			  l+=16;s+=2;
             }
             else
             {
              return;
             }

			} //*s
	 } //while
}




