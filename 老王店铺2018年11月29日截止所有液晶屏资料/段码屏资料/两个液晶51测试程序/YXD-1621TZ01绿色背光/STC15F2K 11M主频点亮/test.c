/*
YXD-1621TZ01

2018/7/24
*/

#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

//D1201����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
sbit D1201_DAT=P3^5;
sbit D1201_CS=P3^2;     //lower enable
sbit D1201_WR=P3^4;     //rising edge
sbit D1201_RD=P3^3;

#include "YXD-1621.c"     //12λ��ʽҺ��
//#include "DelayMs_15F104E6.h"    //15F104 6M��ʱ


sbit LEDA=P3^6;
sbit LEDK=P3^7;


/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned int t)
{
while(--t)
{
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
DelayUs2x(235);
}

}

sfr P3M0        =   0xB2;   //0000,0000 �˿�3ģʽ�Ĵ���0











/*------------------------------------------------
          ��ʼ����ʱ��1,����ɨ�������
------------------------------------------------*/
void Init_Timer1(void)    //ʹ�ö�ʱ��1ɨ�������
{
 TMOD |= 0x10;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ�� 
 TH1=0x00;	      //������ֵ������ʹ�ö�ʱ�����ֵ��0��ʼ����һֱ��65535���
 TL1=0x00;
 EA=1;            //���жϴ�
 ET1=1;           //��ʱ���жϴ�
 TR1=1;           //��ʱ�����ش�
}




unsigned char speed,speed2;

/*------------------------------------------------
                 ��ʱ���ж��ӳ��� 1
				    �����ɨ��
------------------------------------------------*/
void Timer1_isr(void) interrupt 3 using 1
{
   TH1=0xFF;                 //FE0BΪ [200/6]Hz ɨ��Ƶ��
   TL1=0x0B;
   speed++;
   if(speed==speed2) speed=0;
   if(speed==0)
    LEDA=1;
	else
	LEDA=0;
}






/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned char i;

speed2=3;
P3M0=0x40;  //PP 3.6
Init_Timer1();

LEDK=0;

//unsigned char d;

D1201_Init();

/*
while(1)
{
d=1;
 D1201_CS=0;
 D1201WrDataCmd(0);//��RAM�ĵ�ַ4д����?����Ĳ�����ΧΪ:0-31
 SENTDATA(0);
 D1201_CS=1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);


for(i=0;i<8;i++)
{
 D1201_CS=0;
 D1201WrDataCmd(0);//��RAM�ĵ�ַ4д����?����Ĳ�����ΧΪ:0-31
 SENTDATA(d);
 D1201_CS=1;
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 d<<=1;
}

}

*/




cls();
i=1;

while(1)
{



print( i,i%16,0);   
DelayMs(50);

print( i,i%16,1);   
DelayMs(50);


print( i,21,0);  
DelayMs(50);

i++;
if(i==17) 
{
for(i=1;i<17;i++)
 print(i,i%16,1);
DelayMs(1000);
DelayMs(250);
for(i=1;i<17;i++)
 print(i,21,0);
DelayMs(1000);
for(i=1;i<17;i++)
 print(i,i%16,1);
DelayMs(30000);

i=1;
}




}
}

