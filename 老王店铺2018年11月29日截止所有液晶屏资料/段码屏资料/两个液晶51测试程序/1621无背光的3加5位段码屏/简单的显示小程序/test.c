/*
3+5�ޱ��������

STC15F2K40S2 LQFP44 11.0592MHz �����²��� PASS
����������һҹ���������ȶ�

2018/7/25

*/

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

unsigned int n,m;


//IO���ò���PPģʽ����ν���õ�ʱ�������Բ��ý�VCC��
//P3M0=0xF0;   

D1621_Init();
cls();



while(1)
{

n++;
print(1,n%1000/100,0);
print(2,n%100/10,0);
print(3,n%10,0);
DelayMs(50);

m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);
m++;
print(5,m%10000/1000,0);
print(6,m%1000/100,0);
print(7,m%100/10,0);
print(8,m%10,0);
DelayMs(50);

}
}

