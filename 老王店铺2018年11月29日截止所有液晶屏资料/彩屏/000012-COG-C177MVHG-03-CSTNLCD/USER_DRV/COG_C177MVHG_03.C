#include "COG_C177MVHG_03.H"
#define LCD_RES    *((uint32_t *) (( GPIOB_BASE +0x0c-0x40000000 )*32+11*4+0x42000000))  
#define LCD_CS     *((uint32_t *) (( GPIOB_BASE +0x0c-0x40000000 )*32+12*4+0x42000000)) 
#define LCD_A0     *((uint32_t *) (( GPIOB_BASE +0x0c-0x40000000 )*32+13*4+0x42000000)) 
#define LCD_WR     *((uint32_t *) (( GPIOB_BASE +0x0c-0x40000000 )*32+14*4+0x42000000)) 
#define LCD_RD     *((uint32_t *) (( GPIOB_BASE +0x0c-0x40000000 )*32+15*4+0x42000000)) 
#define LCD_PORT GPIOC->ODR
 
/*------LCD初始化---------*/ 		
void Init_COG_C177MVHG_03_H(void); 
/*------LCD写指令---------*/
void  LCDWriteCommand(unsigned char command); 
/*------LCD写数据---------*/
void  LCDWriteData(unsigned int Dot_Data); 
/*------全屏刷图128x160 ---------*/
void Display128x160glmage( const void  * DotDATA); 
/*------清屏---------*/
void ClsLCD(unsigned int clsdata); 
/*------设置XY坐标，画点(//横屏模式160x120，第一象限X(0->128),Y->0-159)---------*/
void DrawDot(unsigned char X,unsigned char Y,unsigned int DotColor); 

//●        Y(0-127)
//画点160X128 |  
//X->(0-127) |
//Y->(0-159) |_______________X(0-159)
//坐标在第一象限 
//void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor)
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor);

//●在指定位置画一个指定大小的空心圆00
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,unsigned int DotColor);

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor);

//输出一个ASCII字符，X=160/8=20(0->19),Y=128/16=8(0->),横屏模式
void LcdPrint1Ascii8X16(unsigned char ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor);

//输出8X16ASCII字符串，X=160/8=20(0->19),Y=128/16=8(0->7),横屏模式
void LcdPrint1AsciiStr8X16(const void * ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor);

void  LCDWriteCommand(unsigned char command)
{
	LCD_CS =0;
	LCD_A0 =0;
  LCD_PORT = command;
	LCD_WR =0;
	LCD_WR =1;	
	LCD_CS =1;	
}
void  LCDWriteData(unsigned int Dot_Data)
{
	LCD_CS =0;
	LCD_A0 =1;
  LCD_PORT = Dot_Data>>8;
	LCD_WR =0;
	LCD_WR =1;	
	
  LCD_PORT = Dot_Data ;
	LCD_WR =0;
	LCD_WR =1;		
	
	LCD_CS =1;	
}	

 


//INIT->S6B33B0A 
void Init_COG_C177MVHG_03_H(void)
{
	LCD_CS =0;
	LCD_RES =0;
	delay_1ms(250);
	LCD_RES =1;
 	delay_1ms(250);
 
	LCDWriteCommand( 0x2C);
	delay_1ms(20);

/*------set OTP mode off---------*/
	LCDWriteCommand( 0xEA);
	delay_1ms(10);
	
/*------set internal osc on---------*/
	LCDWriteCommand( 0x02);
	LCDWriteCommand( 0x01);
	delay_1ms(10);
	
/*------booster1 on---------------*/
	LCDWriteCommand( 0x20);
	LCDWriteCommand( 0x0A);
	delay_1ms(10);   
         
/*------booster1 on---------------*/
	LCDWriteCommand( 0x26);
	LCDWriteCommand( 0x01);
        delay_1ms(10);    

/*------booster1 on and amp on---------*/
	LCDWriteCommand( 0x26);
	LCDWriteCommand( 0x09);
	 delay_1ms(10);  

/*------booster2 on-------------*/
	LCDWriteCommand( 0x26);
	LCDWriteCommand( 0x0b);
	delay_1ms(10);         

/*------booster3 on-------------*/
	LCDWriteCommand( 0x26);
	LCDWriteCommand( 0x0f);
	delay_1ms(10);

/*------temp compsation ratio -0.05%------*/
	LCDWriteCommand( 0x28);
	LCDWriteCommand( 0x01);
	
/*------ram skip area set no skip------*/
	LCDWriteCommand( 0x45);
	LCDWriteCommand(  0x00);

/*------normal display---------*/
	LCDWriteCommand( 0x53);
	LCDWriteCommand( 0x00);

/*------set sdir=0,duty=1/162 swap=0-----*/
	LCDWriteCommand( 0x10);
	LCDWriteCommand( 0x23);		//RGB->0x23,BGR->0X21

/*------set clock fpck=fose/32(Normal)/fpck=fose/16(partial1)-------*/
	LCDWriteCommand( 0x24);
	LCDWriteCommand( 0x11);

/*------GSM=00:65K color,DSG=0,SGF=0,SGP=01,SGM=0--Addressing Mode Set (30H)---*/
	LCDWriteCommand( 0x30);
	LCDWriteCommand( 0x02);//09

/*------row vector type=Diagonal ,INC=111-----*/
	LCDWriteCommand( 0x32);
	LCDWriteCommand( 0x0E);//0e

/*------entry mode set : x addr increce, read modify write off--*/
	LCDWriteCommand( 0x40);
	LCDWriteCommand( 0x00);

/*------y address set from 00 to 127--------*/
	LCDWriteCommand( 0x43);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x7F);		

/*------x address set from 00 to 159--------*/
	LCDWriteCommand( 0x42);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x9F);		

/*------frame set FIM=ON,FIP=1FRAME,N-BLOCK=9-----*/
	LCDWriteCommand( 0x34);
	LCDWriteCommand( 0x89);//cd
	
 
 //此处效果对比度调整，**********************************************************
/*------contrast1 set v1 to 3.757v  max=4v----0x2A,CTRL1*/
	LCDWriteCommand( 0x2a);
	LCDWriteCommand( 0xd1);		/* 0xd1- partial display mode 0  LCDWriteCommand( 0xBB);	*/
	
	
/*------contrast2 set v1 to 3.757v  max=4v--------*/
	LCDWriteCommand( 0x2b);
	LCDWriteCommand( 0x00);		/*partial display mode 1 LCDWriteCommand( 0x20)*/
	delay_1ms(10);
//*********************************************************************************
 

/*------bias set to 1/5 --------*/
	LCDWriteCommand( 0x22);
	LCDWriteCommand(  0x11);//0x11高亮	************************
//  LCDWriteCommand(  0x12);//0X12普通
/*------partial display mode off-------*/
	LCDWriteCommand( 0x55);
	LCDWriteCommand( 0x00);
	
/*------Low frequency set off-------*/
	LCDWriteCommand( 0x36);
	LCDWriteCommand( 0x00);
	
/*-------Scrol lstart line Set-------*/
	LCDWriteCommand(0x5A);
	LCDWriteCommand( 0x00);


/*------display on set--------*/
	delay_1ms(20);
	LCDWriteCommand( 0x51);


 ClsLCD(0x0000);	
  LCD_CS =1;
}

void ClsLCD(unsigned int clsdata)//清屏
{
	unsigned int DotCount;
/*------y address set from 00 to 127--------*/
	LCDWriteCommand( 0x43);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x7F);		

/*------x address set from 00 to 159--------*/
	LCDWriteCommand( 0x42);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x9F);	
	for(DotCount=0;DotCount<128*160;DotCount++)
	{
		LCDWriteData(clsdata);
	}
}


void Display128x160glmage( const void * DotDATA)
{
	unsigned int DotCount;
	u16  * DotDATA_ =(u16 *)DotDATA;
/*------y address set from 00 to 127--------*/
	LCDWriteCommand( 0x43);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x7F);		

/*------x address set from 00 to 159--------*/
	LCDWriteCommand( 0x42);
	LCDWriteCommand( 0x00);
	LCDWriteCommand( 0x9F);	 
	for(DotCount=0;DotCount<128*160;DotCount++)
	{
   		LCDWriteData( * DotDATA_);
    DotDATA_ ++;
  }
}
//横屏模式160x120，第一象限X(0->128),Y->0-159
void DrawDot(unsigned char X,unsigned char Y,unsigned int DotColor)
{
/*------y address set from 00 to 127--------*/
	LCDWriteCommand( 0x43);
	LCDWriteCommand( 127-Y );
	LCDWriteCommand( 0x7F);		

/*------x address set from 00 to 159--------*/
	LCDWriteCommand( 0x42);
	LCDWriteCommand( 159-X );
	LCDWriteCommand( 0x9F);		
/*------write DIPLAY DOT DATA--------*/   
	LCDWriteData(DotColor) ;
	
}


//●        Y(0-127)
//画点160X128 |  
//X->(0-127) |
//Y->(0-159) |_______________X(0-159)
//坐标在第一象限 
//void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor)
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		DrawDot(uRow,uCol,DotColor);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


//在指定位置画一个指定大小的空心圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,unsigned int DotColor)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		DrawDot(x0+a,y0-b,DotColor);             //5
 		DrawDot(x0+b,y0-a,DotColor);             //0           
		DrawDot(x0+b,y0+a,DotColor);             //4               
		DrawDot(x0+a,y0+b,DotColor);             //6 
		DrawDot(x0-a,y0+b,DotColor);             //1       
 		DrawDot(x0-b,y0+a,DotColor);             
		DrawDot(x0-a,y0-b,DotColor);             //2             
  	DrawDot(x0-b,y0-a,DotColor);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,unsigned int DotColor)
{
	LCD_DrawLine(x1,y1,x2,y1,DotColor);
	LCD_DrawLine(x1,y1,x1,y2,DotColor);
	LCD_DrawLine(x1,y2,x2,y2,DotColor);
	LCD_DrawLine(x2,y1,x2,y2,DotColor);
}

//输出一个ASCII字符，X=160/8=20(0->19),Y=128/16=8(0->),横屏模式
void LcdPrint1Ascii8X16(unsigned char ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor)
{
	unsigned char DotCount,bitCount;
	ASCII -=' '; 
/*------y address set from 00 to 127--------*/
	LCDWriteCommand( 0x43);
	LCDWriteCommand( Y*16  );
	LCDWriteCommand( Y*16+15);		

/*------x address set from 00 to 159--------*/
	LCDWriteCommand( 0x42);
	LCDWriteCommand((19-X)*8);
	LCDWriteCommand((19-X)*8+7);	
//	LCDWriteCommand(8);
//	LCDWriteCommand(15);
/*------y address set from 00 to 127--------*/

	

	for(DotCount=0;DotCount<16 ;DotCount++)
	{
			for(bitCount=0;bitCount<8 ;bitCount++)
		{
		   if( ASCII_16X8[ASCII][DotCount] & (1<< bitCount ) )
		      LCDWriteData(FontColor) ;
			 else
			    LCDWriteData(BottomColor) ;
		}
 
	}
}

//输出8X16ASCII字符串，X=160/8=20(0->19),Y=128/16=8(0->7),横屏模式
void LcdPrint1AsciiStr8X16(const void  * ASCII,unsigned char X,unsigned char Y,unsigned int FontColor,unsigned int 	BottomColor)
{
	unsigned char *ASCII_= (unsigned char * )ASCII;
	 while(* ASCII_)
	 {
		LcdPrint1Ascii8X16(* ASCII_, X, Y, FontColor, BottomColor);
		 X++;
		 ASCII_++;
		 if(20==X)
		 {
			 X=0;
		   Y++;
		   if(8 ==Y)
			 {
			   Y =0;
			 }
		 }
   }
}













