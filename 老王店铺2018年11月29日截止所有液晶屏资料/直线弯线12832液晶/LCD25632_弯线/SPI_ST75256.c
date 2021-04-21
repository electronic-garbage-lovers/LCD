#include "SPI_ST75256.h"
#include "lcdfont.h"

/***************************************************************
***************************************************************/
void Delay_uS(unsigned char uS)		//@11.0592MHz
{
	unsigned char i,j;
	for(j=uS;j>0;j--)
	{
		for(i=11;i>0;i--);
	}
}

/***************************************************************
***************************************************************/
void Delay_mS(unsigned int mS)		//@11.0592MHz
{
	unsigned char i,j;
	unsigned int k;
	if (mS==0) return;
	for(k=mS;k>0;k--)
	{
		for(i=11;i>0;i--)
		{
			for(j=190;j>0;j--);
		}
	}
}

/***************************************************************
** ��������: SPI_SendByte
** ��������: �����߷���һ���ֽ�����
** �䡡��:   
** �䡡��:   
** ȫ�ֱ���: 
***************************************************************/
void SPI_SendByte(bit COMMAND,unsigned char dat)
{
    unsigned char i;
    SPI_CSB = 0;
    SPI_A0 = COMMAND;
    for (i=8; i>0; i--)         //8λ������
    {
      SPI_SCL = 0;         //����ʱ����
      dat <<= 1;              //�Ƴ����ݵ����λ
		  SPI_SDA = CY;      //�����ݿ�
			SPI_SCL = 1;                //����ʱ����
    }
    SPI_CSB = 1;
}

/***************************************************************
//��������
***************************************************************/
void ST75256_Set_Pos(unsigned char x_start, unsigned char y_start,unsigned char x_end,unsigned char y_end) 
{
	SPI_SendByte(SPI_COMMAND,0x30);      //EXT=0

	SPI_SendByte(SPI_COMMAND,0x15);      //Clumn Address setting(�����е�ַ) 
	SPI_SendByte(SPI_DATA,x_start);         //
	SPI_SendByte(SPI_DATA,x_end);         //

	SPI_SendByte(SPI_COMMAND,0x75);      // Page Address setting������ҳ��ַ��
	SPI_SendByte(SPI_DATA,y_start);         //
	SPI_SendByte(SPI_DATA,y_end);         //

	SPI_SendByte(SPI_COMMAND,0x5C);      //

}   	  

/***************************************************************
  ��ָ��λ����ʾһ��6x8�ַ�
  x:0~127    y:0~3
***************************************************************/
void ST75256_ShowChar_6x8(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c,i;
	c = chr - ' ';//�õ�ƫ�ƺ��ֵ			

	ST75256_Set_Pos(x,y,x+6,y+1);
	for(i=0;i<6;i++)
	{
		SPI_SendByte(SPI_DATA,F6x8[c][i]);
	}	
}

/***************************************************************
  ��ָ��λ����ʾһ���ַ���
  x:0~127    y:0~4
***************************************************************/
void ST75256_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char i;
	for(i=0;i<(unsigned char)strlen(chr);i++)
	{	
		if(x>250) {x=0;y++;}
		if(y>3) y=0;
		ST75256_ShowChar_6x8(x,y,chr[i]);
		x+=6;
	}
}

/***************************************************************
 ����
***************************************************************/
void ST75256_Clear(void)
{
	unsigned char i,j;
	for (j=0;j<4;j++)
	{
		ST75256_Set_Pos(0,j,0xFF,0x28);
		for (i=0;i<128;i++)	
		{
			SPI_SendByte(SPI_DATA,0);
//			Delay_uS(1);
			SPI_SendByte(SPI_DATA,0);
		}
	}
}

/***************************************************************
 ��ʼ��
***************************************************************/
void ST75256_Init(void)
{ 	
	SPI_RST = 0;
  Delay_mS(10);
	SPI_RST = 1;
  Delay_mS(200);
	SPI_SendByte(SPI_COMMAND,0x30);      //EXT=0
	SPI_SendByte(SPI_COMMAND,0x94);      //Sleep out
	SPI_SendByte(SPI_COMMAND,0xD1);      //Turn on the internal oscillator 
  Delay_mS(50);
	SPI_SendByte(SPI_COMMAND,0xAE);      //display off
	Delay_mS(50);
	SPI_SendByte(SPI_COMMAND,0x20);      //Power control�����ʿ��ƣ�
	SPI_SendByte(SPI_DATA,0x0B);         //VB=VF=VR=1
	Delay_mS(50);

	SPI_SendByte(SPI_COMMAND,0x81);      //EV control 
	SPI_SendByte(SPI_DATA,0x38);         //Vo=8.5V
	SPI_SendByte(SPI_DATA,0x01);

	SPI_SendByte(SPI_COMMAND,0x31);      //EXT=1
/*
	SPI_SendByte(SPI_COMMAND,0x20);
	SPI_SendByte(SPI_DATA,0x01);
	SPI_SendByte(SPI_DATA,0x03);
	SPI_SendByte(SPI_DATA,0x05);
	SPI_SendByte(SPI_DATA,0x07);
	SPI_SendByte(SPI_DATA,0x09);
	SPI_SendByte(SPI_DATA,0x0B);
	SPI_SendByte(SPI_DATA,0x0D);
	SPI_SendByte(SPI_DATA,0x10);
	SPI_SendByte(SPI_DATA,0x11);
	SPI_SendByte(SPI_DATA,0x13);
	SPI_SendByte(SPI_DATA,0x15);
	SPI_SendByte(SPI_DATA,0x17);
	SPI_SendByte(SPI_DATA,0x19);
	SPI_SendByte(SPI_DATA,0x1B);
	SPI_SendByte(SPI_DATA,0x1D);
	SPI_SendByte(SPI_DATA,0x1F);
*/	
	
	SPI_SendByte(SPI_COMMAND,0xD7);      //Set auto-read instruction
	SPI_SendByte(SPI_DATA,0x9F);
	
	SPI_SendByte(SPI_COMMAND,0x32);      //Set analog circuit 
	SPI_SendByte(SPI_DATA,0x00);         //OSC Frequency adjustment
	SPI_SendByte(SPI_DATA,0x01);         //Frequency on booster capacitors- >6KHz
	SPI_SendByte(SPI_DATA,0x05);         //Bias=1/9

	SPI_SendByte(SPI_COMMAND,0x51);      //Booster Level x10
	SPI_SendByte(SPI_DATA,0xFB);
	
	SPI_SendByte(SPI_COMMAND,0x30);      //EXT=0

	SPI_SendByte(SPI_COMMAND,0xF0);      //Display Mode����ʾģʽ��
	SPI_SendByte(SPI_DATA,0x10);         //10=Monochrome Mode,11=4Gray
	
	SPI_SendByte(SPI_COMMAND,0xCA);      //Display Control����ʾ���ƣ�
	SPI_SendByte(SPI_DATA,0x00);
	SPI_SendByte(SPI_DATA,0x1F);         //1/32 duty
	SPI_SendByte(SPI_DATA,0x00);         //Nline=off
	
	SPI_SendByte(SPI_COMMAND,0xBC);      //Data scan direction������ɨ�跽��)
	SPI_SendByte(SPI_DATA,0x00);         //CL=0;MX=0;MY=0

	SPI_SendByte(SPI_COMMAND,0x0C);      //D0=1 (0x0C��D0=1)
	
	SPI_SendByte(SPI_COMMAND,0xA6);      //������
	
	SPI_SendByte(SPI_COMMAND,0x75);      //Page Address setting������ҳ��ַ�� 
	SPI_SendByte(SPI_DATA,0x00);         //Y Start = 0
	SPI_SendByte(SPI_DATA,0x28);         //Y End = 31

	SPI_SendByte(SPI_COMMAND,0x15);      //Clumn Address setting(�����е�ַ) 
	SPI_SendByte(SPI_DATA,0x00);         //X Start = 0
	SPI_SendByte(SPI_DATA,0xFF);         //X End = 255

	SPI_SendByte(SPI_COMMAND,0xAF);      //display on (LCD ��ʾ)

	ST75256_Clear();
}	

