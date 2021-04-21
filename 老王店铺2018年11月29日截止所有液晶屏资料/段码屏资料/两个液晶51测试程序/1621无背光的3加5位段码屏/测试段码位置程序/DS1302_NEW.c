/*
DS1302��ȡ����

2013-3-7 �������ڸ�ʽ����



*/

unsigned char time_buf1[8] = {20,13,3,18,8,28,00,1};//��������ʱ������
unsigned char time_buf[8] ;                         //��������ʱ������
/*------------------------------------------------
           ��DS1302д��һ�ֽ�����
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{

	unsigned char i;
	RST_SET;	
	
	//д��Ŀ���ַ��addr
	addr = addr & 0xFE;     //���λ����
	for (i = 0; i < 8; i ++) 
	    { 
		if (addr & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//д�����ݣ�d
	for (i = 0; i < 8; i ++) 
	   {
		if (d & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		d = d >> 1;
		}
	RST_CLR;					//ֹͣDS1302����
}
/*------------------------------------------------
           ��DS1302����һ�ֽ�����
------------------------------------------------*/

unsigned char Ds1302_Read_Byte(unsigned char addr) 
{

	unsigned char i;
	unsigned char temp;
	RST_SET;	

	//д��Ŀ���ַ��addr
	addr = addr | 0x01;//���λ�ø�
	for (i = 0; i < 8; i ++) 
	    {
	     
		if (addr & 0x01) 
		   {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//������ݣ�temp
	for (i = 0; i < 8; i ++) 
	    {
		temp = temp >> 1;
		if (IO_R) 
		   {
			temp |= 0x80;
			}
		else 
		   {
			temp &= 0x7F;
			}
		SCK_SET;
		SCK_CLR;
		}
	
	RST_CLR;	//ֹͣDS1302����
	return temp;
}

/*------------------------------------------------
           ��DS1302д��ʱ������
------------------------------------------------*/
void Ds1302_Write_Time(void) 
{
     
    unsigned char i,tmp;
	for(i=0;i<8;i++)
	    {                  //BCD����
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	    }
	Ds1302_Write_Byte(ds1302_control_add,0x00);			//�ر�д���� 
	Ds1302_Write_Byte(ds1302_sec_add,0x80);				//��ͣ 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//������ 
	Ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//�� 
	Ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//�� 
	Ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//�� 
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	Ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//ʱ 
	Ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//��
	Ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//��
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д���� 
}

/*------------------------------------------------
           ��DS1302����ʱ������
------------------------------------------------*/
void Ds1302_Read_Time(void)  
{ 
   	    unsigned char i,tmp;
	time_buf[1]=Ds1302_Read_Byte(ds1302_year_add);		//�� 
	time_buf[2]=Ds1302_Read_Byte(ds1302_month_add);		//�� 
	time_buf[3]=Ds1302_Read_Byte(ds1302_date_add);		//�� 
	time_buf[4]=Ds1302_Read_Byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=Ds1302_Read_Byte(ds1302_min_add);		//�� 
	time_buf[6]=(Ds1302_Read_Byte(ds1302_sec_add))&0x7F;//�� 
	time_buf[7]=Ds1302_Read_Byte(ds1302_day_add);		//�� 
  
	for(i=0;i<8;i++)
	   {           //BCD����
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	   }
//Ϊ��ֹ��һ����ʱ����������������
if(time_buf1[1]<13) time_buf1[1]=13;
if(time_buf1[1]>99) time_buf1[1]=99;

if(time_buf1[2]==0) time_buf1[2]=1;
if(time_buf1[2]>12) time_buf1[2]=12;

if(time_buf1[3]==0) time_buf1[3]=1;
if(time_buf1[3]>31) time_buf1[3]=31;

if(time_buf1[4]>23) time_buf1[4]=23;

if(time_buf1[5]>59) time_buf1[5]=59;

if(time_buf1[6]>59) time_buf1[1]=59;

}

/*------------------------------------------------
                DS1302��ʼ��
------------------------------------------------*/
void Ds1302_Init(void)
{
	
	RST_CLR;			//RST���õ�
	SCK_CLR;			//SCK���õ�
//  Ds1302_Write_Time();  //����ʱ��

    Ds1302_Write_Byte(ds1302_sec_add,0x00);				 
}





//////����1302�ȴ�1��//////
void pause()
{
unsigned char s2;
s2=time_buf1[6];
while(s2==time_buf1[6])
 {
  DelayMs(200);
  Ds1302_Read_Time(); 
 }
}


/*---------------------------------------------
1302ʱ�Ӿ��� xΪ��������/�죬��Ϊ���죬��Ϊ����
��Χ-128 �� 127
������
 �õ�ǰʱ�����Ҫ�������������õ�Ҫ�����ķ���ʱ�̣�
  Ȼ���ڸ÷��ӵ�30��ʱ������29��31�롣
2013-4-6
----------------------------------------------*/
void correct1302(signed x)
{
unsigned int t1;             //���ڼ��㵱ǰ�������0:00:00ʱ������


if(time_buf1[6]==30)
{ 
 t1=time_buf1[4]*60+time_buf1[5]+1;  //��ǰʱ�����0:00�ķ�����

   if(x>0)  //����,��һ�룬Ȼ��ȴ�2�룬��ʱ����31��ʱ����������
   {
   if(t1%((1440)/x)==0)  //������Ҫ����1���ʱ��
    {
     time_buf1[6]=29;
     Ds1302_Write_Time(); 
     pause();
	 pause();
    }
   }

   if(x<0) //���� �������������ǰʱ�̼�һ�룬д��1302
    {
    if(t1%((1440)/(0-x))==0)  //������Ҫ����1���ʱ��
	 {
     time_buf1[6]=31;
     Ds1302_Write_Time(); 
	 }
    }
}//end if(time_bufl[6]==30)


}

