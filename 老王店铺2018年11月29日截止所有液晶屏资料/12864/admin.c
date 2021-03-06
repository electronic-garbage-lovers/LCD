//128*64液晶驱动函数（基于sed1565)
//晓熊编写 STC12C5A60S2单片机 4M   UV2编译


//#include <reg51.h>    //51头文件?


#include <STC12C5A60S2.H>  //我用的STC125a60s2,如果用51应该屏蔽
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define _Nop() _nop_(); _nop_()
#define  P_Data  P0 //数据口


sbit RST=P3^0;	      //复位 
sbit AO=P3^1;		  //数据/命令切换
sbit RW=P3^2;		  //写控制
sbit EP=P3^3;		  //时钟


void delay_nms(unsigned int n)       //N ms延时函数
  {
   unsigned int i=0,l=0;
   for (i=0;i<n;i++)
   	{ 
		for (l=0;l<120;l++);
  	}
  }

//delay us
void Delay(uchar us) //5,7,9
{
while(--us);
}


//delay ms
void DelayMS(uint iMs)
{
uint i,j;
for(i=0;i<iMs;i++)
for(j=0;j<65;j++) Delay(1);
}
//========================================================
//字模   纵向取模！！！	
//========================================================
code char hanzi[]={
/*--  文字:  晓  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x7F,0x42,0x42,0x7F,0x00,0x21,0x21,0xE2,0x3A,0x24,0x26,0x29,0x20,0x03,0x00,
0x00,0xF0,0x20,0x20,0xF2,0x84,0x98,0xE0,0x80,0x80,0xFC,0x82,0x02,0x82,0x8E,0x00,

/*--  文字:  熊  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x18,0x37,0xD5,0x15,0x55,0x37,0x18,0x00,0xF9,0x24,0x64,0x25,0x1D,0x00,0x00,
0x00,0x02,0xFC,0x40,0x48,0x56,0xF0,0x00,0x08,0xE6,0x90,0x90,0x18,0x76,0x00,0x00,

/*--  文字:  液  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x86,0x60,0x07,0x18,0x21,0x27,0x38,0x21,0xA6,0x7D,0x24,0x25,0x26,0x20,0x00,
0x20,0x20,0xFF,0x00,0x80,0x00,0xFF,0x82,0x84,0x48,0x30,0xD8,0x86,0x03,0x02,0x00,

/*--  文字:  晶  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x7E,0x54,0x54,0x54,0x54,0x54,0x54,0x7E,0x00,0x00,0x00,0x00,
0x00,0xFE,0xA4,0xA4,0xA4,0xA4,0xFE,0x00,0x00,0xFE,0xA4,0xA4,0xA4,0xA4,0xFE,0x00,

/*--  文字:  测  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x8C,0x61,0x06,0x00,0x7F,0x40,0x4F,0x40,0x7F,0x00,0x1F,0x00,0x00,0xFF,0x00,
0x20,0x3F,0xC0,0x00,0x01,0xE2,0x0C,0xF0,0x08,0xE6,0x00,0xE0,0x02,0x01,0xFE,0x00,

/*--  文字:  试  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0x42,0x3B,0x10,0x00,0x09,0x09,0x09,0x09,0x09,0xFF,0x08,0x48,0x38,0x08,0x00,
0x00,0x00,0xFE,0x04,0x08,0x04,0x04,0xF8,0x08,0x08,0x80,0x60,0x18,0x04,0x1E,0x00,

/*--  文字:  程  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x48,0x4B,0x7F,0x89,0x88,0x01,0xFD,0x85,0x85,0x85,0x85,0xFD,0x01,0x00,0x00,
0x20,0xC0,0x00,0xFF,0x00,0x82,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0x02,0x00,

/*--  文字:  序  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x3F,0x20,0x20,0x28,0x28,0xAC,0x6A,0x29,0x2A,0x2C,0x28,0x20,0x20,0x00,
0x01,0x06,0xF8,0x00,0x80,0x80,0x80,0x82,0x81,0xFE,0x80,0x80,0x80,0xC0,0x80,0x00,

};
//========================================================
//6*16字符	 只有大写字母，51容量小
//========================================================
code char zifu[]={
/*--  文字:     --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  !  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,

/*--  文字:  "  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x30,0x40,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  #  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x09,0x0B,0x3D,0x0B,0x3D,0x09,0x00,0xC0,0x00,0xC0,0x00,0x00,

/*--  文字:  $  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x24,0x7F,0x22,0x31,0x00,0xC0,0x40,0xE0,0x40,0x80,0x00,

/*--  文字:  %  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x24,0x1B,0x0D,0x32,0x01,0x00,0xC0,0x00,0x80,0x40,0x80,

/*--  文字:  &  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x03,0x1C,0x27,0x1C,0x07,0x00,0x80,0x40,0x40,0x80,0x40,0x40,

/*--  文字:  '  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x10,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  (  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x00,0x1F,0x20,0x40,0x00,0x00,0x00,0x80,0x40,0x20,

/*--  文字:  )  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x40,0x20,0x1F,0x00,0x00,0x00,0x20,0x40,0x80,0x00,0x00,

/*--  文字:  *  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x09,0x06,0x1F,0x06,0x09,0x00,0x00,0x00,0x80,0x00,0x00,0x00,

/*--  文字:  +  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x04,0x04,0x3F,0x04,0x04,0x00,0x00,0x00,0x80,0x00,0x00,0x00,

/*--  文字:  ,  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x60,0x00,0x00,0x00,0x00,

/*--  文字:  -  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  .  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,

/*--  文字:  /  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x01,0x06,0x38,0x40,0x00,0x20,0xC0,0x00,0x00,0x00,0x00,

/*--  文字:  0  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x20,0x20,0x20,0x1F,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  1  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x10,0x3F,0x00,0x00,0x00,0x00,0x40,0xC0,0x40,0x00,0x00,

/*--  文字:  2  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x21,0x22,0x24,0x18,0x00,0xC0,0x40,0x40,0x40,0x40,0x00,

/*--  文字:  3  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x10,0x20,0x24,0x24,0x1B,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  4  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x02,0x0D,0x11,0x3F,0x01,0x00,0x00,0x00,0x00,0xC0,0x40,0x00,

/*--  文字:  5  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x3C,0x24,0x24,0x24,0x23,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  6  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x24,0x24,0x34,0x03,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  7  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x30,0x20,0x27,0x38,0x20,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1B,0x24,0x24,0x24,0x1B,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  9  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1C,0x22,0x22,0x22,0x1F,0x00,0x00,0xC0,0x40,0x40,0x80,0x00,

/*--  文字:  :  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,

/*--  文字:  ;  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,

/*--  文字:  <  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x04,0x0A,0x11,0x20,0x40,0x00,0x00,0x00,0x00,0x80,0x40,

/*--  文字:  =  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x09,0x09,0x09,0x09,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  >  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x40,0x20,0x11,0x0A,0x04,0x00,0x40,0x80,0x00,0x00,0x00,

/*--  文字:  ?  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x20,0x23,0x24,0x18,0x00,0x00,0x00,0x40,0x00,0x00,0x00,

/*--  文字:  @  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x20,0x27,0x29,0x1F,0x00,0x80,0x40,0x40,0x40,0x40,0x00,

/*--  文字:  A  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x07,0x39,0x0F,0x01,0x00,0x40,0xC0,0x00,0x00,0xC0,0x40,

/*--  文字:  B  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x24,0x1B,0x00,0x40,0xC0,0x40,0x40,0x80,0x00,

/*--  文字:  C  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x20,0x20,0x20,0x30,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  D  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x20,0x20,0x1F,0x00,0x40,0xC0,0x40,0x40,0x80,0x00,

/*--  文字:  E  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x2E,0x30,0x00,0x40,0xC0,0x40,0x40,0xC0,0x00,

/*--  文字:  F  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x2E,0x30,0x00,0x40,0xC0,0x40,0x00,0x00,0x00,

/*--  文字:  G  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x0F,0x10,0x20,0x22,0x33,0x02,0x00,0x80,0x40,0x40,0x80,0x00,

/*--  文字:  H  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x04,0x04,0x3F,0x20,0x40,0xC0,0x00,0x00,0xC0,0x40,

/*--  文字:  I  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x20,0x3F,0x20,0x20,0x00,0x40,0x40,0xC0,0x40,0x40,0x00,

/*--  文字:  J  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x20,0x20,0x3F,0x20,0x20,0x60,0x20,0x20,0xC0,0x00,0x00,

/*--  文字:  K  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x0B,0x30,0x20,0x40,0xC0,0x40,0x00,0xC0,0x40,

/*--  文字:  L  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x20,0x00,0x00,0x00,0x40,0xC0,0x40,0x40,0x40,0xC0,

/*--  文字:  M  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x3F,0x3C,0x03,0x3C,0x3F,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,

/*--  文字:  N  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x0C,0x23,0x3F,0x20,0x40,0xC0,0x40,0x00,0xC0,0x00,

/*--  文字:  O  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x20,0x20,0x20,0x1F,0x00,0x80,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  P  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x24,0x18,0x00,0x40,0xC0,0x40,0x00,0x00,0x00,

/*--  文字:  Q  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x1F,0x21,0x21,0x20,0x1F,0x00,0x80,0x40,0x40,0xE0,0xA0,0x00,

/*--  文字:  R  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x24,0x26,0x19,0x00,0x40,0xC0,0x40,0x00,0xC0,0x40,

/*--  文字:  S  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x24,0x24,0x22,0x31,0x00,0xC0,0x40,0x40,0x40,0x80,0x00,

/*--  文字:  T  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x30,0x20,0x3F,0x20,0x30,0x00,0x00,0x40,0xC0,0x40,0x00,0x00,

/*--  文字:  U  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3F,0x00,0x00,0x3F,0x20,0x00,0x80,0x40,0x40,0x80,0x00,

/*--  文字:  V  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x3E,0x01,0x07,0x38,0x20,0x00,0x00,0xC0,0x00,0x00,0x00,

/*--  文字:  W  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x38,0x07,0x3C,0x07,0x38,0x00,0x00,0xC0,0x00,0xC0,0x00,0x00,

/*--  文字:  X  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x39,0x06,0x39,0x20,0x00,0x40,0xC0,0x00,0xC0,0x40,0x00,

/*--  文字:  Y  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x20,0x38,0x07,0x38,0x20,0x00,0x00,0x40,0xC0,0x40,0x00,0x00,

/*--  文字:  Z  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x30,0x21,0x26,0x38,0x20,0x00,0x40,0xC0,0x40,0x40,0xC0,0x00,

};
///发送命令子函数
//========================================================
void sendcom(unsigned char da)
{
AO=0;
RW=0;
P_Data=da;
EP=1;		 
EP=0;
}
//========================================================
//写入数据子函数
//========================================================
void senddata(unsigned char da)
{  
AO=1;
RW=0;
P_Data=da;
EP=1;
EP=0;
}



void InitGraphic(void)
{
RST=0;DelayMS(50);
delay_nms(100);
RST=1;
P0=0x00;
sendcom(0xaf);	//LCD_ON								  
sendcom(0x2f);	//上电模式
sendcom(0x81);	//电量设置模式(屏幕亮度)
sendcom(0x30);	//指令数据
sendcom(0x27);	//内部电压调节电阻设置
sendcom(0xA2);	//偏压设置
sendcom(0xc0);	               //sendcom(0xc0);	//Com 扫描方式设置(0xc8反向)
sendcom(0xa0);  //Segment方向选择(0xa1反向)
sendcom(0xa4);  //全屏变亮(0xa5变亮)
sendcom(0xa6);  //正相反相显示控制指令，RAM中数据不变(0xa7)
sendcom(0xac);  //静态指示器控制指令(0xad为on)
sendcom(0x00);  
sendcom(0x40);  //设置显示起始行对应RAM行号
}

//========================================================
//页设置子函数
//========================================================
 void setpage(unsigned char a)
{
a|=0xb0;
sendcom(a);
}
//========================================================
//列设置子函数
//========================================================
void setaddr(unsigned char addr)
{
unsigned char a,b;
a=addr;
a&=0x0f;
b=addr>>4;
b|=0x10;
sendcom(a);
sendcom(b);
}
//========================================================
//清屏子函数     fill ROM with 0 or 1
//========================================================
void ClearScreen(unsigned char a)
{
 int z1,z2;

for(z1=0;z1<8;z1++)
{
setpage(z1);
setaddr(0);
    for(z2=0;z2<=128;z2++)
    {
	   senddata(a);
    }
}
}

//========================================================
//显示16*16汉字
//========================================================
void showhanzi(char x,char y,char n)   //汉字
{

	char i,*p=hanzi;
	y=6-y;
	p+=32*n;
	setpage(y+1);
	setaddr(x);
	for(i=0;i<16;i++)
	{
		senddata(*p);
		p++;
	}
	setpage(y);
	setaddr(x);
	for(i=0;i<16;i++)
	{
		senddata(*p);
		p++;
	}

}
//========================================================
//显示6*16字符
//========================================================
void showzifu(char x,char y,char *n)  
{
	char i,*p;
	y=6-y;	
	while(*n!=0)
	{ 
	    p=zifu;
		p+=12*(*n-32);
		setpage(y+1);
		setaddr(x);
		for(i=0;i<6;i++)
		{
			senddata(*p);
			p++;
		}
		setpage(y);
		setaddr(x);
		for(i=0;i<6;i++)
		{
			senddata(*p);
			p++;
		}
	
		x+=6;
		n++;
	}
	
}



main()
{
	int a=127;
    DelayMS(500);
	InitGraphic();	//初始化
	ClearScreen(0);	//清屏
	showhanzi(0,2,0);  
		showhanzi(17,2,1);	
		showhanzi(33,2,2);	
		showhanzi(49,2,3);
		showhanzi(66,2,4);	
	    showhanzi(82,2,5);
		showhanzi(99,2,6);
		showhanzi(115,2,7);
   	showzifu(16,6,"THIS IS 128*64 TEST");
   	delay_nms(1000);
  	while(1)
	{
		ClearScreen(0);	//清屏
		showhanzi(0,2,0);  
		showhanzi(17,2,1);	
		showhanzi(33,2,2);	
		showhanzi(49,2,3);
		showhanzi(66,2,4);	
	    showhanzi(82,2,5);
		showhanzi(99,2,6);
		showhanzi(115,2,7);
	   	if(a>=-115)
		{
			a-=10;
		}
		else
		{
			a=127;
		}
		showzifu(a,6,"THIS IS 128*64 TEST ");
		delay_nms(800);
		DelayMS(1000);
	}


}



