//--------����ͷ�ļ�---------------------------------------
#include "stc8.h"
#include "code.h"		//�Ұ��ֿⶨ��������ļ���

//--------��������-----------------------------------------
#define uchar unsigned char
#define uint unsigned int

//--------���Ŷ���-----------------------------------------
sbit CS = P2^2;		//Ƭѡ
sbit SDA = P2^3;	//����
sbit SCL = P2^5;	//ʱ��
sbit CD = P7^5;		//ָ��/����ת��
sbit RS = P7^4;		//��λ

//--------������������ѧ�Ķ�����---------------------------
void delayus(uint num);
void delayms(uchar num);
void SPI_SEND(bit CorD,uchar SND);
void LCD_INIT();
void LCD_SEND();
void LCD_CLEAN();

//--------�����ʱ-----------------------------------------
void delayms(uchar num)   //12MHZʱ1ms
{
	uchar i, j;
while(num--)
{
	i = 16;
	j = 147;
	do
	{
		do{
			}	while (--j);
	} while (--i);
}
}

void delayus(uint num)		//12MHZʱ1us
{
	uchar i;
	num >>= 3;							//����3 = ����8 0.25us
	while(num--)						//0.25us
	{
		i=28;									//7.5us
		while(--i);
		}
}


//--------���з���1���ֽ�----------------------------------
void SPI_SEND(bit CorD,uchar SND)
{
	uchar i;
	CS	=	0;				//��Ƭѡ
/*	if(CorD == 0)		//�ж�ָ�������
		CD = 0;
	else CD	=	1;
*/								//�ҷ�����ɵ���ˣ���Ȼ��д���ж�������CD����ʵֱ�Ӹ�ֵ�ͺã�������������������
	CD = CorD;			//ֱ�Ӹ�ֵ
	delayus(1);
	for(i=0;i<8;i++)	//	ѭ��λ�Ʒ���
	{
		SCL	=	0;
		delayus(1);
		if(SND&0x80)
			SDA	=	1;
		else SDA	=	0;
		delayus(1);
		SCL	=	1;
		SND	<<=	1;
		delayus(1);
	}
	CS	=	1;
}


//--------LCD��ʼ��----------------------------------------
void LCD_INIT()
{
	delayms(10);
	RS	= 0;
	delayus(100);
	RS	=	1;
	delayms(255);
  delayms(255);
	delayms(255);
	SPI_SEND(0,0X2F);		//���ڲ���ѹ����ȻҪ���ⲿVLCD
	SPI_SEND(0,0X81);		//Ҫ������Աȶ�
	SPI_SEND(0,0XB0);		//�Աȶ���ֵ�����Ҫ�Լ�����һ�����Ч����
	SPI_SEND(0,0XEB);		//Һ��ƫѹ����  1/9
//	SPI_SEND(0,0XF1);		//Ҫ����������
//	SPI_SEND(0,0X3F);		//����64��
	SPI_SEND(0,0XC2);		//����ɨ�跽ʽ��Ĭ�ϴ����ң��ϵ��¡�
//	SPI_SEND(0,0XA7);		//���÷��ԣ������������Ҫ��ѡ��
	SPI_SEND(0,0XAF);		//����ʾ
}

//-------LCD����-------------------------------------------
void LCD_CLEAN(uchar DAT)
{
	uint i = 192*64/8; //128X64���أ�����RAM��192�еģ���Ҳû���ҵ���������н���λ�á����ݴ�СҪ����8λ����

	for(;i>0;i--)
	SPI_SEND(1,DAT); //DAT =0X00,��ȫ�ף�OXFF����ȫ��
}

//-------LCD��������---------------------------------------
void LCD_SETADD(uchar page,uchar col)
{
col 	-=	1;												//ram��ַ��0��ͷ��
page	-=	1;												//ram��ַ��0��ͷ��
SPI_SEND(0,0xb0|page); 							//����ҳ��ַ
SPI_SEND(0,col&0x0F); 							//ȡ��ַ�ĵ�4λ
	col >>=4;
	col	=	col|0x10;
SPI_SEND(0,col);								//ȡ��4λ�е�ַ
}

//-------LCDд16X16�ַ�-------------------------------------
void LCD_SEND1616(uchar page,uchar col,uchar *P)  //ѧ�����¶�������ָ�루�е�ַ���е�ַ��������ָ�룩
//Ϊ���ܿ���ԭ���Ұ�Ƕ��ѭ�����2��for��д
{
	uchar i;
	LCD_SETADD(page,col);		//���͵�ַ����һҳ
	for (i=0;i<16;i++)				//��һҳ������16�ֽڣ��к��Զ��ۼ�
		{
			SPI_SEND(1,*P); //д���ݵ�LCD�����Ҫ��ɫ��ʾ������*Pǰ��~ȡ����
			P++;
		}
	LCD_SETADD(page+1,col);		//���͵�ַ���ڶ�ҳ
	for (i=0;i<16;i++)				//�ڶ�ҳ������16�ֽ�
		{
			SPI_SEND(1,*P); //д���ݵ�LCD
			P++;
		}
}
//-------LCDд8X16�ַ�-------------------------------------
void LCD_SEND0816(uchar page,uchar col,uchar *P)
{
	uchar i,j;
	for(j=0;j<2;j++)					//������������ŵģ������㻹��Ҫд��ҳ
		{
			LCD_SETADD(page+j,col);
			for (i=0;i<8;i++)
				{
					SPI_SEND(1,*P); 
					P++;
				}
		}
}





void main()
{
	LCD_INIT();
	LCD_CLEAN(0x00);
	LCD_SEND1616(1,1,lao);
	LCD_SEND1616(1,17,wang);
	LCD_SEND1616(1,33,de);
	LCD_SEND0816(1,49,num1);
	LCD_SEND1616(1,57,cun);
	LCD_SEND1616(1,73,ping);
	LCD_SEND1616(1,89,mu);
	LCD_SEND0816(3,1,num1);
	LCD_SEND0816(3,9,num8);
	LCD_SEND0816(3,17,num6);
	LCD_SEND0816(3,25,num6);
	LCD_SEND0816(3,33,num7);
	LCD_SEND0816(3,41,num8);
	LCD_SEND0816(3,49,num6);
	LCD_SEND0816(3,57,num0);
	LCD_SEND0816(3,65,num0);
	LCD_SEND0816(3,73,num0);
	LCD_SEND0816(3,81,num0);
	delayus(1);
}