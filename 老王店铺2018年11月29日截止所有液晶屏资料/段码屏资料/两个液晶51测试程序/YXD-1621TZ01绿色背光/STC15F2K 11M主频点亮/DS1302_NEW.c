/*
DS1302读取程序

2013-3-7 增加日期格式条件



*/

unsigned char time_buf1[8] = {20,13,3,18,8,28,00,1};//空年月日时分秒周
unsigned char time_buf[8] ;                         //空年月日时分秒周
/*------------------------------------------------
           向DS1302写入一字节数据
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{

	unsigned char i;
	RST_SET;	
	
	//写入目标地址：addr
	addr = addr & 0xFE;     //最低位置零
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
	
	//写入数据：d
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
	RST_CLR;					//停止DS1302总线
}
/*------------------------------------------------
           从DS1302读出一字节数据
------------------------------------------------*/

unsigned char Ds1302_Read_Byte(unsigned char addr) 
{

	unsigned char i;
	unsigned char temp;
	RST_SET;	

	//写入目标地址：addr
	addr = addr | 0x01;//最低位置高
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
	
	//输出数据：temp
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
	
	RST_CLR;	//停止DS1302总线
	return temp;
}

/*------------------------------------------------
           向DS1302写入时钟数据
------------------------------------------------*/
void Ds1302_Write_Time(void) 
{
     
    unsigned char i,tmp;
	for(i=0;i<8;i++)
	    {                  //BCD处理
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	    }
	Ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
	Ds1302_Write_Byte(ds1302_sec_add,0x80);				//暂停 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//涓流充电 
	Ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//年 
	Ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//月 
	Ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//日 
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//周 
	Ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//时 
	Ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//分
	Ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//秒
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//周 
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护 
}

/*------------------------------------------------
           从DS1302读出时钟数据
------------------------------------------------*/
void Ds1302_Read_Time(void)  
{ 
   	    unsigned char i,tmp;
	time_buf[1]=Ds1302_Read_Byte(ds1302_year_add);		//年 
	time_buf[2]=Ds1302_Read_Byte(ds1302_month_add);		//月 
	time_buf[3]=Ds1302_Read_Byte(ds1302_date_add);		//日 
	time_buf[4]=Ds1302_Read_Byte(ds1302_hr_add);		//时 
	time_buf[5]=Ds1302_Read_Byte(ds1302_min_add);		//分 
	time_buf[6]=(Ds1302_Read_Byte(ds1302_sec_add))&0x7F;//秒 
	time_buf[7]=Ds1302_Read_Byte(ds1302_day_add);		//周 
  
	for(i=0;i<8;i++)
	   {           //BCD处理
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	   }
//为防止第一次走时出错，增加修正条件
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
                DS1302初始化
------------------------------------------------*/
void Ds1302_Init(void)
{
	
	RST_CLR;			//RST脚置低
	SCK_CLR;			//SCK脚置低
//  Ds1302_Write_Time();  //重置时间

    Ds1302_Write_Byte(ds1302_sec_add,0x00);				 
}





//////利用1302等待1秒//////
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
1302时钟纠正 x为纠正秒数/天，正为调快，负为调慢
范围-128 至 127
方法：
 用当前时间除以要调整的秒数，得到要调整的分钟时刻，
  然后在该分钟的30秒时，调到29或31秒。
2013-4-6
----------------------------------------------*/
void correct1302(signed x)
{
unsigned int t1;             //用于计算当前日期相对0:00:00时的秒数


if(time_buf1[6]==30)
{ 
 t1=time_buf1[4]*60+time_buf1[5]+1;  //当前时间相对0:00的分钟数

   if(x>0)  //调慢,减一秒，然后等待2秒，让时间是31秒时返回主程序
   {
   if(t1%((1440)/x)==0)  //到了需要调整1秒的时刻
    {
     time_buf1[6]=29;
     Ds1302_Write_Time(); 
     pause();
	 pause();
    }
   }

   if(x<0) //调快 方法：计算出当前时刻加一秒，写入1302
    {
    if(t1%((1440)/(0-x))==0)  //到了需要调整1秒的时刻
	 {
     time_buf1[6]=31;
     Ds1302_Write_Time(); 
	 }
    }
}//end if(time_bufl[6]==30)


}

