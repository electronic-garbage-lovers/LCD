/******************************************************/  
//#include <reg51.h>    //51Í·ÎÄ¼ş¬


#include <STC12C5A60S2.H>  //ÎÒÓÃµÄSTC125a60s2,Èç¹ûÓÃ51Ó¦¸ÃÆÁ±Î
#include <intrins.h>

#define uint unsigned int  
#define uchar unsigned char 

#define _Nop() _nop_(); _nop_();




//LCD_ST7920´®ĞĞ²âÊÔ³ÌĞò (2010-10-25 17:30:23)×ªÔØ¨

//#include <ziku.h>



sbit CS  = P1^5;      //Æ¬Ñ¡ĞÅºÅ
sbit SID = P1^6;      //´®ĞĞÊı¾İ
sbit SCLK = P1^7;      //´®ĞĞÍ¬²½Ê±ÖÓ
//sbit PSB = P1^3;        //´®²¢¿ÚÑ¡Ôñ 1:²¢¿ÚÄ£Ê½; 0:´®¿ÚÄ£Ê½;


#define CLEAR_SCREEN 0x01   //ÇåÆÁÖ¸Áî£ºÇåÆÁÇÒACÖµÎª00H
#define AC_INIT   0x02   //½«ACÉèÖÃÎª00H¡£ÇÒÓÎ±êÒÆµ½Ô­µãÎ»ÖÃ
#define CURSE_ADD  0x06   //Éè¶¨ÓÎ±êÒÆµ½·½Ïò¼°Í¼ÏñÕûÌåÒÆ¶¯·½Ïò£¨Ä¬ÈÏÓÎ±êÓÒÒÆ£¬Í¼ÏñÕûÌå²»¶¯£©
#define FUN_MODE  0x30   //¹¤×÷Ä£Ê½£º8Î»»ù±¾Ö¸Áî¼¯
#define DISPLAY_ON  0x0c   //ÏÔÊ¾¿ª,ÏÔÊ¾ÓÎ±ê£¬ÇÒÓÎ±êÎ»ÖÃ·´°×
#define DISPLAY_OFF  0x08   //ÏÔÊ¾¹Ø
#define CURSE_DIR  0x14   //ÓÎ±êÏòÓÒÒÆ¶¯:AC=AC+1
#define SET_CG_AC  0x40   //ÉèÖÃAC£¬·¶Î§Îª£º00H~3FH
#define SET_DD_AC  0x80


uchar code addr_tab[]={
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,//µÚÒ»ĞĞºº×ÖÎ»ÖÃ
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,//µÚ¶şĞĞºº×ÖÎ»ÖÃ
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,//µÚÈıĞĞºº×ÖÎ»ÖÃ
0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,//µÚËÄĞĞºº×ÖÎ»ÖÃ
};


void Delay(uchar us) //5,7,9
{
while(--us);
}


//delay ms
void delayms(uint iMs)
{
uint i,j;
for(i=0;i<iMs;i++)
{for(j=0;j<120;j++) Delay(1);}
}

void SendByte(uchar Dbyte)
{
     uchar i;
     for(i=0;i<8;i++)
     {
           SCLK = 0;
           Dbyte=Dbyte<<1;        //×óÒÆÒ»Î»
           SID = CY;              //ÒÆ³öµÄÎ»¸øSID
           SCLK = 1;_Nop()
           SCLK = 0;
     }
}


uchar ReceiveByte(void)
{
     uchar i,temp1,temp2;
     temp1 = 0;
     temp2 = 0;
     for(i=0;i<8;i++)
     {
           temp1=temp1<<1;
           SCLK = 0;_Nop()
           SCLK = 1; _Nop()         
           SCLK = 0;
           if(SID) temp1++;
     }
     for(i=0;i<8;i++)
     {
           temp2=temp2<<1;
           SCLK = 0;_Nop()
           SCLK = 1;_Nop()
           SCLK = 0;
           if(SID) temp2++;
     }
     return ((0xf0&temp1)+(0x0f&temp2));
}


void CheckBusy( void )
{
     do   SendByte(0xfc);         //11111,RW(1),RS(0),0
     while(0x80&ReceiveByte());       //BF(.7)=1 Busy
}


void Lcd_WriteCmd(uchar Cbyte )
{
     CS = 1;
     CheckBusy();
     SendByte(0xf8);              //11111,RW(0),RS(0),0
     SendByte(0xf0&Cbyte);        //¸ßËÄÎ»
     SendByte(0xf0&Cbyte<<4);   //µÍËÄÎ»(ÏÈÖ´ĞĞ<<)
     CS = 0;
}


void Lcd_WriteData(uchar Dbyte )
{
     CS = 1;
     CheckBusy();
     SendByte(0xfa);              //11111,RW(0),RS(1),0
     SendByte(0xf0&Dbyte);        //¸ßËÄÎ»
     SendByte(0xf0&Dbyte<<4);   //µÍËÄÎ»(ÏÈÖ´ĞĞ<<)
     CS = 0;
}


void Lcd_Init(void)
{
//    PSB = 0;
 delayms(10);
    Lcd_WriteCmd(0x30);        //Ñ¡Ôñ»ù±¾Ö¸Áî¼¯
 delayms(1);
    Lcd_WriteCmd(0x30);          //Ñ¡Ôñ8bitÊı¾İÁ÷
 delayms(1);
    Lcd_WriteCmd(0x0c);          //¿ªÏÔÊ¾(ÎŞÓÎ±ê¡¢²»·´°×)
 delayms(1);
    Lcd_WriteCmd(0x01);          //Çå³ıÏÔÊ¾£¬²¢ÇÒÉè¶¨µØÖ·Ö¸ÕëÎª00H
 delayms(10);
}


void hanzi_Disp(uchar x,uchar y,uchar code *s)
{
 Lcd_WriteCmd(addr_tab[8*x+y]);  //Ğ´µØÖ·
 while(*s>0)
    {
  Lcd_WriteData(*s);    //Ğ´Êı¾İ
  s++;   
    }
}


 main(void)
{
 Lcd_Init();
 while(1)
 {
  Lcd_Init();
  hanzi_Disp(0,0,"ÄãºÃ£¡12232LCD");
  hanzi_Disp(1,0,"Òº¾§²âÊÔ³ÌĞò");
  delayms(1500);   
  }
}
