/*
����1���������� v2017

ռ�ö�ʱ��0��1
���� STC89C STC90C
STC12C STC15C


���жϽ�������

rec��ʾ��������������
cpʵʱ����ָ��
Uart[] �������ݻ�����

2016/9/22

�޸Ĵ�Ʒ�������ݵ��㷨
ռ�ö�ʱ��0�Ͷ�ʱ��1
��ʱ��0��Ϊ�жϴ��ڽ��ճ�ʱ������
��ʱ��1�Ǵ��ڵĲ����ʷ�����

ʹ�ö��л���������������С xdata 256�ֽ�
ʹ�ý����ַ���ʱ�㷨��ÿ���յ����ݣ�������ʱ��������Ϊ1
�ö�ʱ����ͣ���ۼ���ʱ��ʱ��������ʱ��ʱ���ۼӵ�һ�������ݺ�
�Ϳ�����Ϊ�յ���һ������
�ڶ�ʱ��0���жϴ����У�����һ������ת�浽Uart��ȥ��ͬʱ��λ��λ��ز���
Ŀǰ���ڶ�ʱ��0��Ϊ 0xF000������£���11.0592MHz��Ƶ��STC12C5A08S2��Ƭ����
��9600bps������£����������Ľ�������
rec���յ��ַ����ĳ���

ʹ�÷�����
�������ں����������У���Ҫ�ж�rec�Ƿ�Ϊ�㣬Ϊ���ʾû���յ��ַ�������Ϊ��
��ʾ�յ��ַ����ĳ��ȣ��ַ����� Uart[]�У��Ϊ255���ֽڣ������ַ�����Ӧ�ý�
rec���㣬������һ�ξͲ�֪����û���յ��µ��ַ�����

2017-2-10

*/
#define cache_max 16
unsigned char rec;   //���յ��ַ����ĳ���, 0û���յ�
unsigned char cache[cache_max];  //���ݽ��ջ�����
unsigned char cp;    //cache ������ָ��
unsigned char rec_delay;   //���ڽ������ݺ�Ŀ���ʱ���ۼ���
unsigned char last_cp;     //��һ�δ����յ����ݺ��ڻ�����е���һ���հ�λ��

#define FOSC 11059200L
//#define FOSC 22118400L          //ϵͳƵ��
//#define BAUD 9600             //���ڲ�����
#define BAUD 9600

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

#define PARITYBIT NONE_PARITY

sfr AUXR  = 0x8e;               //�����Ĵ���

sfr P_SW1   = 0xA2;             //���蹦���л��Ĵ���1

#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

sfr T2H   = 0xd6;               //��ʱ��2��8λ
sfr T2L   = 0xd7;               //��ʱ��2��8λ

bit busy;





/*----------------------------
UART1 interrupt service routine
----------------------------*/
void Uar89t() interrupt 4 using 1
{
    if (RI)
    { 
        cache[cp] = SBUF;   //�յ����ַ�����cache
        RI = 0;            //���RIλ
        cp++;
		if(cp==cache_max) cp=0;
        rec_delay=1;       //�ó�ʱ��ʱ��Ϊ1
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        busy = 0;               //��æ��־
    }
}

/*----------------------------
Send a unsigned char data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void Com_SendByte(unsigned char dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
    busy = 1;
    SBUF = dat;                 //д���ݵ�UART���ݼĴ���
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendStr(char *s)
{
    while (*s)              //Check the end of the string
    {
        Com_SendByte(*s++);     //Send current char and increment string ptr
    }
}




/*----------------------------
        com1 ��ʼ��
----------------------------*/
void InitUART()
{
    ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
    
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
//  ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
//  P_SW1 = ACC;  
//  
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
//  ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
//  P_SW1 = ACC;  

#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8λ�ɱ䲨����
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif


#ifdef STC15W408AS
    T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
    ES = 1;                     //ʹ�ܴ���1�ж�
    EA = 1;
#endif
#ifdef STC12C 
///////////// STC12C5A08S2 ��1T��ʱ���������ʿ��Ը���
    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ                STC12 STC15
    TMOD = 0x20;                //��ʱ��1Ϊģʽ2(8λ�Զ�����)
    TL1 = (256 - (FOSC/32/BAUD));   //���ò�������װֵ
    TH1 = (256 - (FOSC/32/BAUD));
    TR1 = 1;                    //��ʱ��1��ʼ����
    ES = 1;                     //ʹ�ܴ����ж�
    EA = 1;
#endif
#ifdef STC90C
////////////// STC89C51��12��Ƶ��ʱ��
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode   STC89C STC90C
    TH1 = TL1 = -(FOSC/12/32/BAUD); //Set auto-reload vaule
    TR1 = 1;                    //��ʱ��1��ʼ����
    ES = 1;                     //ʹ�ܴ����ж�
    EA = 1;
#endif


	last_cp=0;                  //�������հ׵Ŀ�ʼλ��
	rec_delay=0;                //����������ʱ�ۼ������ж�һ���ݽ����ı�־
    rec=0;                      //���յ����ݵĳ�������
	cp=0;                       //��������ָ������
//	Init_time0();               //������ʱ��0�����ڼ��㳬ʱ��������������
}
