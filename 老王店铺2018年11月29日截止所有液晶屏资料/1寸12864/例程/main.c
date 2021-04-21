//--------包含头文件---------------------------------------
#include "stc8.h"
#include "code.h"		//我把字库定义在这个文件中

//--------常量定义-----------------------------------------
#define uchar unsigned char
#define uint unsigned int

//--------引脚定义-----------------------------------------
sbit CS = P2^2;		//片选
sbit SDA = P2^3;	//数据
sbit SCL = P2^5;	//时钟
sbit CD = P7^5;		//指令/数据转换
sbit RS = P7^4;		//复位

//--------函数声明（新学的东西）---------------------------
void delayus(uint num);
void delayms(uchar num);
void SPI_SEND(bit CorD,uchar SND);
void LCD_INIT();
void LCD_SEND();
void LCD_CLEAN();

//--------软件延时-----------------------------------------
void delayms(uchar num)   //12MHZ时1ms
{
	uchar i, j;
while(num--)
{
	i = 16;
	j = 147;
	do
	{
		do{
			}	while (--j);
	} while (--i);
}
}

void delayus(uint num)		//12MHZ时1us
{
	uchar i;
	num >>= 3;							//右移3 = 除以8 0.25us
	while(num--)						//0.25us
	{
		i=28;									//7.5us
		while(--i);
		}
}


//--------串行发送1个字节----------------------------------
void SPI_SEND(bit CorD,uchar SND)
{
	uchar i;
	CS	=	0;				//开片选
/*	if(CorD == 0)		//判断指令还是数据
		CD = 0;
	else CD	=	1;
*/								//我发现我傻逼了，居然还写个判断来决定CD，其实直接赋值就好，保留在这里留作提醒
	CD = CorD;			//直接赋值
	delayus(1);
	for(i=0;i<8;i++)	//	循环位移发送
	{
		SCL	=	0;
		delayus(1);
		if(SND&0x80)
			SDA	=	1;
		else SDA	=	0;
		delayus(1);
		SCL	=	1;
		SND	<<=	1;
		delayus(1);
	}
	CS	=	1;
}


//--------LCD初始化----------------------------------------
void LCD_INIT()
{
	delayms(10);
	RS	= 0;
	delayus(100);
	RS	=	1;
	delayms(255);
  delayms(255);
	delayms(255);
	SPI_SEND(0,0X2F);		//开内部升压，不然要接外部VLCD
	SPI_SEND(0,0X81);		//要求输入对比度
	SPI_SEND(0,0XB0);		//对比度数值，这个要自己试验一下最佳效果。
	SPI_SEND(0,0XEB);		//液晶偏压设置  1/9
//	SPI_SEND(0,0XF1);		//要求设置行数
//	SPI_SEND(0,0X3F);		//行数64；
	SPI_SEND(0,0XC2);		//设置扫描方式，默认从左到右，上到下。
//	SPI_SEND(0,0XA7);		//设置反显，加在这里，有需要的选用
	SPI_SEND(0,0XAF);		//开显示
}

//-------LCD清屏-------------------------------------------
void LCD_CLEAN(uchar DAT)
{
	uint i = 192*64/8; //128X64像素，但是RAM是192列的，我也没有找到如何设置列结束位置。数据大小要除以8位数据

	for(;i>0;i--)
	SPI_SEND(1,DAT); //DAT =0X00,清全白，OXFF，清全黑
}

//-------LCD设置坐标---------------------------------------
void LCD_SETADD(uchar page,uchar col)
{
col 	-=	1;												//ram地址是0开头。
page	-=	1;												//ram地址是0开头。
SPI_SEND(0,0xb0|page); 							//设置页地址
SPI_SEND(0,col&0x0F); 							//取地址的低4位
	col >>=4;
	col	=	col|0x10;
SPI_SEND(0,col);								//取高4位行地址
}

//-------LCD写16X16字符-------------------------------------
void LCD_SEND1616(uchar page,uchar col,uchar *P)  //学到个新东西叫做指针（行地址，列地址，数组名指针）
//为了能看懂原理，我把嵌套循环拆成2个for来写
{
	uchar i;
	LCD_SETADD(page,col);		//发送地址，第一页
	for (i=0;i<16;i++)				//第一页的数据16字节，列号自动累加
		{
			SPI_SEND(1,*P); //写数据到LCD，如果要反色显示，就在*P前用~取反。
			P++;
		}
	LCD_SETADD(page+1,col);		//发送地址，第二页
	for (i=0;i<16;i++)				//第二页的数据16字节
		{
			SPI_SEND(1,*P); //写数据到LCD
			P++;
		}
}
//-------LCD写8X16字符-------------------------------------
void LCD_SEND0816(uchar page,uchar col,uchar *P)
{
	uchar i,j;
	for(j=0;j<2;j++)					//这逼字体是竖着的，所以你还是要写两页
		{
			LCD_SETADD(page+j,col);
			for (i=0;i<8;i++)
				{
					SPI_SEND(1,*P); 
					P++;
				}
		}
}





void main()
{
	LCD_INIT();
	LCD_CLEAN(0x00);
	LCD_SEND1616(1,1,lao);
	LCD_SEND1616(1,17,wang);
	LCD_SEND1616(1,33,de);
	LCD_SEND0816(1,49,num1);
	LCD_SEND1616(1,57,cun);
	LCD_SEND1616(1,73,ping);
	LCD_SEND1616(1,89,mu);
	LCD_SEND0816(3,1,num1);
	LCD_SEND0816(3,9,num8);
	LCD_SEND0816(3,17,num6);
	LCD_SEND0816(3,25,num6);
	LCD_SEND0816(3,33,num7);
	LCD_SEND0816(3,41,num8);
	LCD_SEND0816(3,49,num6);
	LCD_SEND0816(3,57,num0);
	LCD_SEND0816(3,65,num0);
	LCD_SEND0816(3,73,num0);
	LCD_SEND0816(3,81,num0);
	delayus(1);
}