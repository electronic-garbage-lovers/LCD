
#include "kfm010b11.H"


#define LcdCs  *((uint32_t *)  (( GPIOC_BASE +0x0c-0x40000000 )*32+0*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdRst  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+1*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdA0  *((uint32_t *)  (( GPIOC_BASE +0x0c-0x40000000 )*32+2*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdSck  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+3*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdSda  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+4*4+0x42000000))  //GPIOC_DOR bit8 add
 
 
//PAGE_8
//0->天线标记	
//4->天线信号最小挡	
//7 ->天线信号中挡		
//10 ->天线信号高挡	
//20 ->电话听筒标记	
//30 ->电话锁标记
//40 ->字母Gr标记	
//50 ->信箱标记		
//60 ->锁标记		
//70 ->禁止铃声标记	
//75 ->闹钟标记		
//80 ->电池外壳标记	
//93 ->电池电量高标记	
//94 ->电池电量低标记	
//95 ->电池电量中标记	 


void LCD_SendCom(unsigned char COM);
void LCD_SendData(unsigned char Data);
void clear_lcd_kfm010b11(void);
 
//●●●●●LCD发送指令
void LCD_SendCom(unsigned char COM)
{
	unsigned char shift;
 	volatile	uint8_t * ComBit7=(uint8_t *) (((uint32_t )(&COM)- 0x20000000)*32+7*4+0x22000000);	
	LcdA0 =0;
  LcdCs =0;
	for(shift=0;shift<8;shift++)
		{
			LcdSda = * ComBit7;
			LcdSck =0;
	//  delay_1ms(1);
			LcdSck =1;
			COM <<=1;
		}
	 LcdCs =1;
}
//●●●●●LCD发送数据
void LCD_SendData(unsigned char Data)
{
	unsigned char shift;
 	volatile	uint8_t * ComBit7=(uint8_t *) (((uint32_t )(&Data)- 0x20000000)*32+7*4+0x22000000);	
	LcdA0 =1;
  LcdCs =0;
		for(shift=0;shift<8;shift++)
		{
			LcdSda = * ComBit7;
			LcdSck =0;
	//  delay_1ms(1);
			LcdSck =1;
			Data <<=1;
		}
	 LcdCs =1;
}

//●●●●●清屏
void clear_lcd_kfm010b11(void)
  {
		int i; 
	 
		LCD_SendCom(0x78);
		LCD_SendCom(0x40);
		for(i = 0; i < 102*9; i++)
		{
		 LCD_SendData(0x00); 
		}  
  }
//●●●●●初始化LCD
void init_kfm010b11(void)
{

	LcdRst=0;
	LcdSck =1;
	LcdCs =0;
	delay_1ms(50);
	LcdRst=1;
	delay_1ms(50);
  LCD_SendCom(0x78);// 
	LCD_SendCom(0x00);//NOP 
	LCD_SendCom(0x2e);//MXMY Mirror X, Mirror Y	
  LCD_SendCom(0x21);//Function set->Extend Set H=1
	LCD_SendCom(0x10);//Bia->对比度调整0b0000xxx
	LCD_SendCom(0xc0);//VOP 
	LCD_SendCom(0x0b);//oost
	LCD_SendCom(0x20);//Function set->Normal Set H=0 
  LCD_SendCom(0x11);//PRS 
	LCD_SendCom(0x0c);// 
	LCD_SendCom(0x40);// 
 	LCD_SendCom(0x80);//PD->en  
	LCD_SendCom(0x20);//Function set->Normal Set H=0	
  clear_lcd_kfm010b11( ); //SET H=0
	LcdCs =1;
}

////●●●●●Sets X address of RAM 0≦X≦95 (//SET H=0)
//void SetXAdd(unsigned char X)
//{
//	LCD_SendCom(0x80+X);
//}

////●●●●●Sets Y address of RAM  0≦Y≦7 (//SET H=0)
//void SetYAdd(unsigned char Y)
//{
//	LCD_SendCom(0x40+Y);
//}



//●●●●●●输出96X64图片
void PrintLcd96x64(const unsigned char *bpm)
{
	unsigned char X_count,Y_count;
	for(Y_count=0;Y_count<8;Y_count++)
	{
		  LCD_SendCom(0x80+00);//set RAM 0≦X≦95
			LCD_SendCom(0x40+Y_count);//Sets Y address of RAM  0≦Y≦7 (//SET H=0)

	 for(X_count=0;X_count<96;X_count++)
			{
			   LCD_SendData(*bpm);//send data
				  bpm++;
			}
  }
}

////●●●●●测试
//void test_sendByte(unsigned char x,unsigned char y )
//{
//   LCD_SendCom(0x80+90+5);//set RAM 0≦X≦95
//	LCD_SendCom(0x40+8);//Set  Y address of RAM  0≦Y≦7 (//SET H=0)
//	LCD_SendData(0xff);//send data

////PAGE_8
////0->天线标记	
////4->天线信号最小挡	
////7 ->天线信号中挡		
////10 ->天线信号高挡	
////20 ->电话听筒标记	
////30 ->电话锁标记
////40 ->字母Gr标记	
////50 ->信箱标记		
////60 ->锁标记		
////70 ->禁止铃声标记	
////75 ->闹钟标记		
////80 ->电池外壳标记	
////93 ->电池电量高标记	
////94 ->电池电量低标记	
////95 ->电池电量中标记	
//}
//●●●●●●输出一个字符 一行96/6=16个字符,0-7行LINE
void Print_a_Ascii8x8(unsigned char Ascii,unsigned char line,unsigned char Number)
{
	unsigned char X_Count;
	Number *=6 ;//列位置计算.一个字符8列,共96列
  line =7-line ;//行反转,由于0行在最底下,改动到7行最上面位置

  LCD_SendCom(0x80+Number);//set RAM 0≦X≦95 列位置(96/8=12)
	LCD_SendCom(0x40+line);//Set  Y address of RAM  0≦Y≦7 (//SET H=0)
	for(X_Count=1;X_Count < 7 ;X_Count ++)
		{		
		  LCD_SendData( ASCII8x8[ Ascii- ' ' ][X_Count]);//send data
	  }
}	
//●●●●●●输出串字符 一行96/6=16个字符,0-7行LINE
void Print_Str_Ascii8x8(void *StrAscii,unsigned char line,unsigned char Number)
{
	  unsigned char * StrAscii_temp =(unsigned char *) StrAscii;
 while(*StrAscii_temp)
 {

   Print_a_Ascii8x8( *StrAscii_temp, line, Number);
	 StrAscii_temp++;
	 Number ++;
   if(Number>>4)
	 {
	    Number =0;
		  line++;
		  line %=8;
	 }
 } 
	
}


//●●●●●●输出一个字符宽8x高16 一行96/8=12个字符,0-3行LINE
void Print_a_Ascii8x16(unsigned char Ascii,unsigned char line,unsigned char Number)
{
	unsigned char X_Count;
	Number *=8 ;//列位置计算.一个字符8列,共96列
  line =(3-line)*2 ;//行反转,由于0行在最底下,改动到96行最上面位置

  LCD_SendCom(0x80+Number);//set RAM 0≦X≦95 列位置(96/8=12)
	LCD_SendCom(0x40+line);//Set  Y address of RAM  0≦Y≦7 (//SET H=0)
	for(X_Count=0;X_Count < 8 ;X_Count ++)
		{		
		  LCD_SendData( ASCII_16X8_H[ Ascii- ' ' ][X_Count+8]);//send data
	  }
		
   LCD_SendCom(0x80+Number);//set RAM 0≦X≦95 列位置(96/8=12)
	LCD_SendCom(0x40+line+1);//Sets Y address of RAM  0≦Y≦7 (//SET H=0)
	for(X_Count=0;X_Count < 8;X_Count ++)
		{		
		  LCD_SendData( ASCII_16X8_H[ Ascii- ' ' ][X_Count]);//send data
	  }
		
}


//●●●●●●输出一个字符 一行96/8=12个字符,0-3行LINE
void Print_Str_Ascii8x16(void *StrAscii,unsigned char line,unsigned char Number)
{
	 unsigned char * StrAscii_temp =(unsigned char *) StrAscii;
	 while(*StrAscii_temp)
		 {
       Print_a_Ascii8x16( *StrAscii_temp, line, Number);
			 StrAscii_temp++;
			 Number ++;
		   if(Number/12)
				 {
					 Number =0;
					 line++;
					 if( 4 == line )
					 {
							line  =0;
					 }
				 }
		 } 
	
}
 

//●●●●●●开窗口显示,X(0-7Page,1Page=1BYTE),Y(0->95)
//注意高度为8得倍数,Y(0->95)
//Display_windows(gImage_48x48, 1,7,0,48);


//void Display_windows(const unsigned char * DotData, unsigned char StartX,unsigned char EndX,unsigned char StartY,unsigned char EndY)
//{
//   unsigned char StartY_TEMP ;
//	StartX = 7-StartX;
//	EndX =7-EndX;
//	 
// for(  ; StartX >EndX ; StartX--)
//	{
//		LCD_SendCom(0x40+StartX);//Sets Y address of RAM  0≦Y≦7 (//SET H=0)
//		LCD_SendCom(0x80+StartY );//Set X //set RAM 0≦X≦95
//		
//	for(StartY_TEMP=0 ;StartY_TEMP<(EndY-StartY);StartY_TEMP++)
//	  {
//				 LCD_SendData(* DotData);
//			   DotData++;
//		 }
//	}
//}










