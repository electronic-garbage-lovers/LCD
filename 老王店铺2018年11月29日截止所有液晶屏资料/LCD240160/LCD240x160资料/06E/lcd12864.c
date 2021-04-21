/*------------------------------
LCD 12864 SPI Һ������������

�������� 1.8 �� 12864�ϲ���ͨ��
��Ƭ�� 15F2K40S2 11.0592MHz

������û�п���CS��
CS���Ѿ�Ӳ����GND

2018-10-17
------------------------------*/






void DelayUs2x(unsigned char t)
{   
 while(--t);
}
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

void delay(void)
{
    unsigned char i,j;
    for (i = 0;i != 0xff;i++)
    for (j = 0;j != 0xff;j++) ;
}



/*------------------------------
Һ��д�����
rs=0ʱд�����ָ��dat
rs=1ʱд����ʾ����dat
------------------------------*/
void send2LCM(bit rs,unsigned char dat )
{
    unsigned char i;
    _RS = rs;
    for (i=0;i<8;i++)
    {
        CLK = 0;
        SID = dat>>7;
        // ����Ƶ����20MHzʱ��������Ҫ����һ����ʱ�����߼�һ���������õ��������ʱ
        dat = dat<<1;
        CLK = 1;
    }
}
void lcdclear(unsigned char dat)/*д�������ݵ�LCDȫ��*/
{
    unsigned char i,j;
    for(i = 0xb0;i<0xb9;i++)
    { 
        send2LCM(0,i); //дҳ��ַ
        send2LCM(0,0x10); //д��ʼ�е�ַ  //0x10
        send2LCM(0,0x02);                 //����д0x02�����0x00�ұ���С�� 
        for(j = 0x00;j<0x41;j++)
        {
            send2LCM(1,dat); //д��ʾ����
            send2LCM(1,dat); //д��ʾ����
        }  //�����������Ǵ�12232�ƹ����ģ�������������
    }
}
void init12864(void)    /*��ʼ��LCM*/
{
    DelayMs(15);
    RST=0;   //3.3vʱ����һ��Ҫȥ��
    DelayMs(15);
    RST=1;
    DelayMs(15);
    send2LCM(0,0xe2); /*�����λ*/
    DelayMs(15);
    send2LCM(0,0xa2); /*LCD BIAS=1/9*/
    send2LCM(0,0xa0); /*�е�ַ�ƶ�����:ADC=0(SEG1->SEG132)*/
    send2LCM(0,0xc8); /*��ɨ�跽��:SHL=1(COM64->COM1)*/
    delay();
    send2LCM(0,0x2f); /*��Դ����ģʽ��VC,VR,VF=111*/
    delay();
    send2LCM(0,0x26); /*�ڲ�����������ʣ�R2,R1,R0=111*/
    delay();
    send2LCM(0,0x81); /*�ԱȶȼĴ���ģʽ*/
    send2LCM(0,0x4A); /*�Աȶ� ��ɫ��12864ʱд0x6F��������
                      // 1.8����5vʱд0x9F�� 3.3vʱд0x5F
                      //1.8�� 5v 0x98����û�е׻�
    send2LCM(0,0x40); /*��ʼ��*/
    send2LCM(0,0xe0); /*д������ʱ�е�ַ�Զ���1������ʱ����*/
    send2LCM(0,0xaf); /*����ʾ*/
}

