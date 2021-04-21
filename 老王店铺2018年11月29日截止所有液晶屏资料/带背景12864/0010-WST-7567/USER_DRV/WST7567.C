
#include "WST7567.H"


#define LcdCs  *((uint32_t *)  (( GPIOC_BASE +0x0c-0x40000000 )*32+0*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdRst  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+1*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdA0  *((uint32_t *)  (( GPIOC_BASE +0x0c-0x40000000 )*32+2*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdSck  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+3*4+0x42000000))  //GPIOC_DOR bit8 add
#define LcdSda  *((uint32_t *) (( GPIOC_BASE +0x0c-0x40000000 )*32+4*4+0x42000000))  //GPIOC_DOR bit8 add
//LCD发送指令
#define PAGE_0 0XB0
#define Set_EV 0x81 
void WST7567_SendCom(unsigned char COM)
{
	unsigned char shift;
 	volatile	uint8_t * ComBit7=(uint8_t *) (((uint32_t )(&COM)- 0x20000000)*32+7*4+0x22000000);	
	LcdA0 =0;
	for(shift=0;shift<8;shift++)
	{
	  LcdSda = * ComBit7;
		LcdSck =0;
//		delay_1ms(1);
		LcdSck =1;
		COM <<=1;
	}
}
//LCD发送数据
void WST7567_SendData(unsigned char Data)
{
	unsigned char shift;
 	volatile	uint8_t * ComBit7=(uint8_t *) (((uint32_t )(&Data)- 0x20000000)*32+7*4+0x22000000);	
	LcdA0 =1;
	for(shift=0;shift<8;shift++)
	{
	  LcdSda = * ComBit7;
		LcdSck =0;
//		delay_1ms(1);
		LcdSck =1;
		Data <<=1;
	}
}

 

//初始化LCD
void init_WST7567(void)
{
	LcdSck =1;
	LcdCs =0;
	LcdRst =0;
	delay_1ms(300);
  LcdRst =1;
	delay_1ms(300);
	
  WST7567_SendCom(0xe2);//Soft rest
 // delay_1ms(10);
  WST7567_SendCom(0x2c);
//  delay_1ms(10);
  WST7567_SendCom(0x2e);
//  delay_1ms(10);
  WST7567_SendCom(0x2f); 
//  delay_1ms(10);
  WST7567_SendCom(0xaf);
  WST7567_SendCom(0x25);
	WST7567_SendCom(0xc0);//(15) COM Direction上下翻转(0xc0.0XC8)
	
	WST7567_SendCom(Set_EV);//Set EV_COM(0x81) 设置EV电压(对比度)指令
	WST7567_SendCom(0x29);  //EV数据0b00??????
	
  WST7567_SendCom(0xb0 );//SET PAGE 0
  WST7567_SendCom( 0xaf);//DisPlay On	
 
//	WST7567_SendCom( 0xA2 ) ; //
//	WST7567_SendCom( 0xA0 ) ;
//	WST7567_SendCom( 0xC8 ) ;
//	WST7567_SendCom( 0x40 ) ;
//	
//	 
// 	WST7567_SendCom( 0x2c ) ;
//	delay_1ms(10);
//	WST7567_SendCom( 0x2e ) ;
//	delay_1ms(10);
//	WST7567_SendCom( 0x2f ) ;
//	delay_1ms(10);
// 
//  WST7567_SendCom( 0x26 ) ; //set Regulation Ratio (0B00100xxx) set Display
//	
//	WST7567_SendCom( 0x81 ) ;  //
//	WST7567_SendCom( 0X1A ) ;   //set dispay 00-63 00xxxxxx   Set EV
//	
//	WST7567_SendCom( 0xaf ) ;
//	WST7567_SendCom( 0xb0 ) ;
//	
//	WST7567_SendCom( 0x10 ) ;
//	WST7567_SendCom( 0x00 ) ; 
 
}



//设置列0-163
void SET_Column(unsigned char Column)
{
		WST7567_SendCom(0x10 | Column>>4 );
		WST7567_SendCom( Column & 0x0f );

}




//设置页
void SET_PAGE(unsigned char Page)
{
	WST7567_SendCom( PAGE_0 +Page);//Set Page(0-7)
}



//清屏
void WST7567_CLS(unsigned char CLS_Data)
{
	unsigned char PAGE,Column_scan ;
 
 	 
	for(PAGE= PAGE_0;PAGE <(PAGE_0 +8);PAGE ++)
	{
		WST7567_SendCom( PAGE );//Set Page(0-7)
		SET_Column(0);
		
 	   for(Column_scan=0;Column_scan<128;Column_scan++)
		  {    
		     WST7567_SendData(CLS_Data);
		  }
 	  
	}
	 
}


//输出12864图片
void printLCD12864( const void *  data)
{
   unsigned char * data_Temp=(unsigned char *)data ;
		unsigned char PAGE,Column_scan ;
 
 	 
	for(PAGE= PAGE_0;PAGE <(PAGE_0 +8);PAGE ++)
	{
		WST7567_SendCom( PAGE );//Set Page(0-7)
		SET_Column(0);
 	   for(Column_scan=0;Column_scan<128;Column_scan++)
		  {    
		     WST7567_SendData( * data_Temp);
				data_Temp++;
		  }
 	  
	}

}


void print_ASCII8X5(unsigned char ASCII,unsigned char Page,unsigned char Column )
{
	unsigned char Column_scan;
	WST7567_SendCom( PAGE_0 +Page);////设置页Set Page(0-7)
		WST7567_SendCom(0x10 | Column>>4 );//设置列Column0-163
		 WST7567_SendCom( Column & 0x0f );
	for(Column_scan=0;Column_scan<6;Column_scan++  )
	{
	   WST7567_SendData( ASCII_8X5[ASCII - ' '][Column_scan]);
	}
}

void Print_ASCII_Str(void const*  ASCI_str,unsigned char Page,unsigned char Column)
{
		unsigned char Column_scan;
	unsigned char * _ASCI_str=(unsigned char *)ASCI_str;
	WST7567_SendCom( PAGE_0 +Page);////设置页Set Page(0-7)
		WST7567_SendCom(0x10 | Column>>4 );//设置列Column0-163
		 WST7567_SendCom( Column & 0x0f );	
  while(* _ASCI_str)
	{
	for(Column_scan=0;Column_scan<6;Column_scan++  )
	  {
	     WST7567_SendData( ASCII_8X5[* _ASCI_str - ' '][Column_scan]);
	  }
		
	_ASCI_str++;
		
	}

}
