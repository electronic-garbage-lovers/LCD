/*
串口1的驱动程序 v2017

占用定时器0，1
兼容 STC89C STC90C
STC12C STC15C


用中断接收数据

rec表示缓冲区的数据量
cp实时数据指针
Uart[] 接收数据缓冲区

2016/9/22

修改串品接收数据的算法
占用定时器0和定时器1
定时器0作为判断串口接收超时计数器
定时器1是串口的波特率发生器

使用队列缓冲区，缓冲区大小 xdata 256字节
使用接收字符超时算法，每次收到数据，都将延时计数器置为1
用定时器不停的累加延时定时器，当延时定时器累加到一定的数据后
就可以认为收到了一桢数据
在定时器0的中断处理中，将这一桢数据转存到Uart中去，同时置位复位相关参数
目前，在定时器0设为 0xF000的情况下，用11.0592MHz主频，STC12C5A08S2单片机，
在9600bps的情况下，可以正常的接收数据
rec是收到字符串的长度

使用方法：
启动串口后，在主程序中，需要判断rec是否为零，为零表示没有收到字符串，不为零
表示收到字符串的长度，字符串在 Uart[]中，最长为255个字节，处理定字符串后，应该将
rec清零，否则下一次就不知道有没有收到新的字符串了

2017-2-10

*/
#define cache_max 16
unsigned char rec;   //接收到字符串的长度, 0没有收到
unsigned char cache[cache_max];  //数据接收缓冲区
unsigned char cp;    //cache 的数据指针
unsigned char rec_delay;   //串口接收数据后的空闲时间累加器
unsigned char last_cp;     //上一次串口收到数据后，在缓冲队列的下一个空白位置

#define FOSC 11059200L
//#define FOSC 22118400L          //系统频率
//#define BAUD 9600             //串口波特率
#define BAUD 9600

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

#define PARITYBIT NONE_PARITY

sfr AUXR  = 0x8e;               //辅助寄存器

sfr P_SW1   = 0xA2;             //外设功能切换寄存器1

#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

sfr T2H   = 0xd6;               //定时器2高8位
sfr T2L   = 0xd7;               //定时器2低8位

bit busy;





/*----------------------------
UART1 interrupt service routine
----------------------------*/
void Uar89t() interrupt 4 using 1
{
    if (RI)
    { 
        cache[cp] = SBUF;   //收到的字符存入cache
        RI = 0;            //清除RI位
        cp++;
		if(cp==cache_max) cp=0;
        rec_delay=1;       //置超时计时器为1
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
    }
}

/*----------------------------
Send a unsigned char data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void Com_SendByte(unsigned char dat)
{
    while (busy);               //等待前面的数据发送完成
    busy = 1;
    SBUF = dat;                 //写数据到UART数据寄存器
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
        com1 初始化
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
    SCON = 0x50;                //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif


#ifdef STC15W408AS
    T2L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
    ES = 1;                     //使能串口1中断
    EA = 1;
#endif
#ifdef STC12C 
///////////// STC12C5A08S2 的1T定时器，波特率可以更高
    AUXR = 0x40;                //定时器1为1T模式                STC12 STC15
    TMOD = 0x20;                //定时器1为模式2(8位自动重载)
    TL1 = (256 - (FOSC/32/BAUD));   //设置波特率重装值
    TH1 = (256 - (FOSC/32/BAUD));
    TR1 = 1;                    //定时器1开始工作
    ES = 1;                     //使能串口中断
    EA = 1;
#endif
#ifdef STC90C
////////////// STC89C51的12分频定时器
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode   STC89C STC90C
    TH1 = TL1 = -(FOSC/12/32/BAUD); //Set auto-reload vaule
    TR1 = 1;                    //定时器1开始工作
    ES = 1;                     //使能串口中断
    EA = 1;
#endif


	last_cp=0;                  //缓冲区空白的开始位置
	rec_delay=0;                //接收数据延时累加器，判断一数据结束的标志
    rec=0;                      //接收到数据的长度清零
	cp=0;                       //接收数据指针清零
//	Init_time0();               //启动定时器0，用于计算超时，给出接收数据
}
