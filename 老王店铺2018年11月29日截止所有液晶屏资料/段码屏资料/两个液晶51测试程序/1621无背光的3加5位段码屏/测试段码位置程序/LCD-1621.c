/*---------------------
LCD-v5.3 �ޱ��� 3+5λ��ʽҺ��
----------------------*/


#define BIAS 0x52//0b1000 0101 0010?1/3duty 4com
#define SYSDIS 0X00//0b1000 0000 0000?����ϵͳ������LCDƫѹ������
#define LCDOFF 0X04//0b1000 0000 0100?��LCDƫѹ
#define LCDON 0X06//0b1000 0000 0110?��LCDƫѹ
#define SYSEN 0X02//0b1000 0000 0010 ��ϵͳ����
#define XTAL 0x28//0b1000 0010 1000 �ⲿ��ʱ��
#define RC256 0X30//0b1000 0011 0000?�ڲ�ʱ��
#define TONEON 0X12//0b1000 0001 0010?���������
#define TONEOFF 0X10//0b1000 0001 0000 �ر��������
#define WDTDIS 0X0A//0b1000 0000 1010?��ֹ���Ź�




unsigned char code DM_CODE[]={0x5F,0x06,0x3D,0x2f,0x66,0x4b,0x7b,0x0E,0x7F,0x6F,0xEE,0x76,0xF0,0x3E,0xf4,0xE4,0xFE,0xFE,0x1,0x6d,0x31,0x00,0x40,0x6e,0x54,0x50,0x5c,0x1c};// ����ֵ
//////////////////////////////  0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    g    H    .    S    T    ��   -    y    n    r    o    u
////////////////////////////////////////////////////////////////////////////////10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27

//���дһ���������ͷ(100)
void D1201WrCmd(unsigned char ucTmpCmd)
{
unsigned char data i,ucCmdByte=0x80;
D1201_CS=0;
_nop_();
_nop_();
for (i=0;i<4;i++)
{
 if (ucCmdByte&0x80)
   D1201_DAT=1;
  else 
   D1201_DAT=0;
 D1201_WR=0;
 _nop_();
 _nop_();
 D1201_WR=1;
 _nop_();
 ucCmdByte<<=1;
}
for (i=0;i<8;i++)
{
if (ucTmpCmd&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucTmpCmd<<=1; 
}
D1201_CS=1;
_nop_();
_nop_(); 
}

//д����+��ַ
void D1201WrDataCmd(unsigned char ucAddr)
{
unsigned char data i,ucDataCmd=0x05;//101
ucDataCmd<<=5;
for (i=0;i<3;i++)
{
if (ucDataCmd&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucDataCmd<<=1; 
}
ucAddr<<=2;
for (i=0;i<6;i++)
{
if (ucAddr&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucAddr<<=1;
}
}


//���дһ���ֽ�����
void SENTDATA(unsigned char ucTmpData)
{
unsigned char data i;
for (i=0;i<8;i++)
{
if (ucTmpData&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_(); 
ucTmpData<<=1;
}
}


void D1621_Init()
{
unsigned char i;
D1201_CS=1;
D1201_WR=0;
D1201_DAT=1;

for(i=0;i<0x80;i++)
_nop_(); 

D1201WrCmd(BIAS);
D1201WrCmd(RC256);//ʹ���ڲ�����
D1201WrCmd(SYSDIS);
D1201WrCmd(WDTDIS);
D1201WrCmd(SYSEN);
D1201WrCmd(LCDON);
}





/*-----------------------------------------------
           print��ӡ����
xλ�ã� ��ʾ dat�� dp��С����λ��0����ʾ��1��ʾ
------------------------------------------------*/
void print(unsigned char x,unsigned char dat,bit dp)
{
 D1201_CS=0;
 D1201WrDataCmd(x+x-2);//��RAM�ĵ�ַ4д����?����Ĳ�����ΧΪ:0-31

 if(dp)
   SENTDATA(DM_CODE[dat]|0x01);
  else
   SENTDATA(DM_CODE[dat]);

 D1201_CS=1;
}



/*--------------
      ����
---------------*/
void cls()
{
unsigned char i;
 D1201_CS=0;
 D1201WrDataCmd(0);//��RAM�ĵ�ַ4д����?����Ĳ�����ΧΪ:0-31
 for(i=0;i<17;i++)
 SENTDATA(0);
 D1201_CS=1;
}
