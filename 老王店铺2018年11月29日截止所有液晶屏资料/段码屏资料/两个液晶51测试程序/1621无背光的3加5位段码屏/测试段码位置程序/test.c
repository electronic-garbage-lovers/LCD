/*
�ޱ���������� 1621����

2018-7-25 �細����
*/
// ������һ��λ�ã��������λ����0,2,4 11,13,15,17����4λ���Ǹ������͵���678910��5��4bit  20bit
#define WEI 11

#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

//D1201����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
sbit D1201_DAT=P3^5;
sbit D1201_CS=P3^2;     //lower enable
sbit D1201_WR=P3^4;     //rising edge
sbit D1201_RD=P3^3;

#include "LCD-1621.c"     //3+5λ��ʽҺ���ޱ��� 0.5Ԫ LCD-V5.3 5v����Ч�����
//#include "DelayMs_15F104E6.h"    //15F104 6M��ʱ

sfr P3M0        =   0xB2;   //0000,0000 �˿�3ģʽ�Ĵ���0






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








/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned char i;
unsigned char d;


//P3M0=0xF0;

D1621_Init();  //��ʼ��

cls();  //����

while(1)
{
d=1;  //���� 00000001 (B)

D1201_CS=0;  //CS��Ч

for(i=0;i<8;i++)
{

 D1201_CS=0;

 D1201WrDataCmd(WEI);//׼��д���λ��
 SENTDATA(d); //д������ݣ�Ҳ���Ƕ���

 D1201_CS=1;  //CS��Ч���ſ�����

 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);

 d<<=1;  //�ı�һ�¶��룬����������ˣ���Ҫ��һ����51������C����

}

}







}

