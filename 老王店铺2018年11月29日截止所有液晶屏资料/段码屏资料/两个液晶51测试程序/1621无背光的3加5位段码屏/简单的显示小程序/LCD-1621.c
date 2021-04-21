/*---------------------
LCD-v5.3 无背光 3+5位段式液晶

段码特殊
第123位数字段码和5678位不一样
第4位是米字型特殊段码

2018-7-26

----------------------*/


#define BIAS 0x52//0b1000 0101 0010?1/3duty 4com
#define SYSDIS 0X00//0b1000 0000 0000?关振系统荡器和LCD偏压发生器
#define LCDOFF 0X04//0b1000 0000 0100?关LCD偏压
#define LCDON 0X06//0b1000 0000 0110?打开LCD偏压
#define SYSEN 0X02//0b1000 0000 0010 打开系统振荡器
#define XTAL 0x28//0b1000 0010 1000 外部接时钟
#define RC256 0X30//0b1000 0011 0000?内部时钟
#define TONEON 0X12//0b1000 0001 0010?打开声音输出
#define TONEOFF 0X10//0b1000 0001 0000 关闭声音输出
#define WDTDIS 0X0A//0b1000 0000 1010?禁止看门狗



// 前3位段码
unsigned char code DM_CODE1[]={0x5F,0x06,0x3D,0x2f,0x66,0x6b,0x7b,0x0E,0x7F,0x6F,0x7E,0x73,0x59,0x37,0x79,0x78,0xFE,0xFE,0x1,0x6d,0x31,0x00,0x40,0x6e,0x54,0x50,0x5c,0x1c};// 段码值
///////////////// /////////////  0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    g    H    .   S    T    空   -    y    n    r    o    u
////////////////// //////////////////////////////////////////////////////////////10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27

// 第5678位段码
unsigned char code DM_CODE2[]={0x9F,0x06,0x3D,0x2f,0xA6,0xAb,0xbb,0x0E,0xbF,0xAF,0xBE,0xB3,0x99,0x37,0xB9,0xB8,0xFE,0xFE,0x1,0x6d,0x31,0x00,0x40,0x6e,0x54,0x50,0x5c,0x1c};// 段码值
///////////////// /////////////  0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    g    H    .   S    T    空   -    y    n    r    o    u
////////////////// //////////////////////////////////////////////////////////////10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27


//完成写一个命令包括头(100)
void D1201WrCmd(unsigned char ucTmpCmd)
{
unsigned char data i,ucCmdByte=0x80;
D1201_CS=0;
_nop_();
_nop_();
for (i=0;i<4;i++)
{
 if (ucCmdByte&0x80)
   D1201_DAT=1;
  else 
   D1201_DAT=0;
 D1201_WR=0;
 _nop_();
 _nop_();
 D1201_WR=1;
 _nop_();
 ucCmdByte<<=1;
}
for (i=0;i<8;i++)
{
if (ucTmpCmd&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucTmpCmd<<=1; 
}
D1201_CS=1;
_nop_();
_nop_(); 
}

//写命令+地址
void D1201WrDataCmd(unsigned char ucAddr)
{
unsigned char data i,ucDataCmd=0x05;//101
ucDataCmd<<=5;
for (i=0;i<3;i++)
{
if (ucDataCmd&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucDataCmd<<=1; 
}
ucAddr<<=2;
for (i=0;i<6;i++)
{
if (ucAddr&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_();
ucAddr<<=1;
}
}


//完成写一个字节数据
void SENTDATA(unsigned char ucTmpData)
{
unsigned char data i;
for (i=0;i<8;i++)
{
if (ucTmpData&0x80) D1201_DAT=1;
else D1201_DAT=0;
D1201_WR=0;
_nop_();
_nop_();
D1201_WR=1;
_nop_(); 
ucTmpData<<=1;
}
}


void D1621_Init()
{
unsigned char i;
D1201_CS=1;
D1201_WR=0;
D1201_DAT=1;

for(i=0;i<0x80;i++)
_nop_(); 

D1201WrCmd(BIAS);
D1201WrCmd(RC256);//使用内部振荡器
D1201WrCmd(SYSDIS);
D1201WrCmd(WDTDIS);
D1201WrCmd(SYSEN);
D1201WrCmd(LCDON);
}





/*-----------------------------------------------
           print打印程序
x位置， 显示 dat， dp是小数点位，0不显示，1显示
------------------------------------------------*/
void print(unsigned char x,unsigned char dat,bit dp)
{
unsigned char w;
w=0;
D1201_CS=0;
if(x<4)
{
 w=x+x-2;
 D1201WrDataCmd(w);
 if(dp)
 SENTDATA(DM_CODE1[dat]+0x80);
 else
 SENTDATA(DM_CODE1[dat]);

}
if(x>4)
{
 w=x+x+1;
 D1201WrDataCmd(w);
 if(dp)
 SENTDATA(DM_CODE2[dat]+0x40);
 else
 SENTDATA(DM_CODE2[dat]);
}
D1201_CS=1;
}



/*--------------
      清屏
---------------*/
void cls()
{
unsigned char i;
 D1201_CS=0;
 D1201WrDataCmd(0);//往RAM的地址4写数据?这里的参数范围为:0-31
 for(i=0;i<17;i++)
 SENTDATA(0);
 D1201_CS=1;
}
