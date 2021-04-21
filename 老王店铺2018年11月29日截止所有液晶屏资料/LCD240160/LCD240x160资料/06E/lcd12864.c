/*------------------------------
LCD 12864 SPI 液晶屏驱动程序

本程序在 1.8 寸 12864上测试通过
单片机 15F2K40S2 11.0592MHz

本程序没有控制CS脚
CS脚已经硬件接GND

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
液晶写入程序
rs=0时写入控制指令dat
rs=1时写入显示数据dat
------------------------------*/
void send2LCM(bit rs,unsigned char dat )
{
    unsigned char i;
    _RS = rs;
    for (i=0;i<8;i++)
    {
        CLK = 0;
        SID = dat>>7;
        // 当主频超过20MHz时，这里需要增加一点延时，或者加一至几条无用的语句以延时
        dat = dat<<1;
        CLK = 1;
    }
}
void lcdclear(unsigned char dat)/*写测试数据到LCD全屏*/
{
    unsigned char i,j;
    for(i = 0xb0;i<0xb9;i++)
    { 
        send2LCM(0,i); //写页地址
        send2LCM(0,0x10); //写初始列地址  //0x10
        send2LCM(0,0x02);                 //这里写0x02，如果0x00右边有小点 
        for(j = 0x00;j<0x41;j++)
        {
            send2LCM(1,dat); //写显示数据
            send2LCM(1,dat); //写显示数据
        }  //这个程序可能是从12232移过来的，用了两个参数
    }
}
void init12864(void)    /*初始化LCM*/
{
    DelayMs(15);
    RST=0;   //3.3v时，这一句要去除
    DelayMs(15);
    RST=1;
    DelayMs(15);
    send2LCM(0,0xe2); /*软件复位*/
    DelayMs(15);
    send2LCM(0,0xa2); /*LCD BIAS=1/9*/
    send2LCM(0,0xa0); /*列地址移动方向:ADC=0(SEG1->SEG132)*/
    send2LCM(0,0xc8); /*行扫描方向:SHL=1(COM64->COM1)*/
    delay();
    send2LCM(0,0x2f); /*电源控制模式：VC,VR,VF=111*/
    delay();
    send2LCM(0,0x26); /*内部调整电阻比率：R2,R1,R0=111*/
    delay();
    send2LCM(0,0x81); /*对比度寄存器模式*/
    send2LCM(0,0x4A); /*对比度 绿色大12864时写0x6F基本正常
                      // 1.8屏，5v时写0x9F， 3.3v时写0x5F
                      //1.8寸 5v 0x98基本没有底灰
    send2LCM(0,0x40); /*起始行*/
    send2LCM(0,0xe0); /*写入数据时列地址自动加1，但读时不变*/
    send2LCM(0,0xaf); /*开显示*/
}

