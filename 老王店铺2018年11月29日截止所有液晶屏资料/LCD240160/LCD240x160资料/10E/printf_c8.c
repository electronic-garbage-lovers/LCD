/*------------------------------
Font 8x6�����ֿ��ӡ����
�������� 1.8��12864SPI�ϲ���ͨ��

2018-10-17
------------------------------*/


#include "f8x6.c"
void printf_c(unsigned char x,unsigned char y, unsigned char c)
{
unsigned char i;
c-=' ';
x+=2;
send2LCM(0,y+0xb0);
send2LCM(0,0x10 | x>>4);
send2LCM(0,x & 0x0f);
for (i=0;i<6;i++)
 send2LCM(1,F6x8[c][i]);
}