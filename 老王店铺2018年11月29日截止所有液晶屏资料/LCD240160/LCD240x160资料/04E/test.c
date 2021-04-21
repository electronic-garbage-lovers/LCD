/* 


*/
#include <reg52.H>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int


sbit lcd_rs=P1^1; 
sbit lcd_en=P1^2;
sbit lcd_wr=P1^3; 
sbit lcd_reset=P1^4;
sbit lcd_cs1=P1^0; 

#define DataPort P0   //DataBUS


/*延时：1 毫秒的i 倍*/
void delay(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<510;k++);
}
/*延时：1us 的i 倍*/
void delay_us(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<10;k++);
}

//并口方式
//写指令到LCD 模块
void transfer_command_lcd(int data1)
{
lcd_rs=0;
lcd_en=1;
P0=data1;P0=data1;P0=data1;P0=data1;
lcd_en=0;
}

//写数据到LCD 模块
void transfer_data_lcd(int data1)
{
lcd_rs=1;
lcd_en=1;
P0=data1;P0=data1;P0=data1;P0=data1;
lcd_en=0;
}


void initial_lcd()
{
lcd_wr=0; 
lcd_cs1=0;  
lcd_reset=0; 
delay(150);
lcd_reset=1;
delay(150);

 
transfer_command_lcd(0x30); //EXT=0 
transfer_command_lcd(0x94); //Sleep out 
transfer_command_lcd(0x31); //EXT=1 
transfer_command_lcd(0xD7); //Autoread disable 
transfer_data_lcd(0X9F); // 
transfer_command_lcd(0x32); //Analog SET 
transfer_data_lcd(0x00); //OSC Frequency adjustment 
transfer_data_lcd(0x01); //Frequency on booster capacitors->6KHz 
transfer_data_lcd(0x03); //Bias=1/13 
transfer_command_lcd(0x20); //灰度设置 
transfer_data_lcd(0x01); 
transfer_data_lcd(0x03); 
transfer_data_lcd(0x05); 
transfer_data_lcd(0x07); 
transfer_data_lcd(0x09); 
transfer_data_lcd(0x0b); 
transfer_data_lcd(0x0d); 
transfer_data_lcd(0x10); 
transfer_data_lcd(0x11); 
transfer_data_lcd(0x13); 
transfer_data_lcd(0x15); 
transfer_data_lcd(0x17); 
transfer_data_lcd(0x19); 
transfer_data_lcd(0x1b); 
transfer_data_lcd(0x1d); 
transfer_data_lcd(0x1f); 
transfer_command_lcd(0x30); //EXT1=0，EXT0=0,表示选择了“扩展指令表 1” 
transfer_command_lcd(0x75); //页地址设置 
transfer_data_lcd(0X00); //起始页地址：YS=0X00 
transfer_data_lcd(0X14); //结束页地址：YE=0x1F每 4 行为一页，第 0～3 行为第 0 页，第 124～127 行为第 31 页（31=0x1f） 
transfer_command_lcd(0x15); //列地址设置 
transfer_data_lcd(0X00); //起始列地址：XS=0 
transfer_data_lcd(0Xef); //结束列地址：XE=240（0xef） 
transfer_command_lcd(0xbc); //行列扫描方向 
transfer_data_lcd(0x02); //MX.MY=Normal 
// transfer_command_lcd(0x0c); //数据格式选择,0x0C 是低位在前 D0-D7,0x08 是高位在前 D7-D0 
transfer_command_lcd(0xCA); //显示控制 
transfer_data_lcd(0X00); //设置 CL 驱动频率：CLD=0 
transfer_data_lcd(0X9F); //占空比：Duty=160 
transfer_data_lcd(0X20); //N 行反显：Nline=off 
transfer_command_lcd(0xF0); //显示模式 
transfer_data_lcd(159); //如果设为 0x11：表示选择 4 灰度级模式，如果设为 0x10:表示选择黑白模式 
transfer_command_lcd(0x81); //设置对比度，“0x81”不可改动，紧跟着的 2 个数据是可改的，但“先微调后粗调”这 
transfer_data_lcd(0x80);  //微调对比度,可调范围 0x00～0x3f，共 64 级 0
transfer_data_lcd(0x03); //粗调对比度,可调范围 0x00～0x07，共 8 级 
transfer_command_lcd(0x20); //电源控制 
transfer_data_lcd(0x0B); //D0=regulator ; D1=follower ; D3=booste, on:1 off:0 
delay_us(200); 
transfer_command_lcd(0xAF); //打开显示 
}





/*写LCD 行列地址：X 为起始的列地址，Y 为起始的行地址，x_total,y_total 分别为列地址及行地址的起点到终点的差值 */
void lcd_address(int x,int y,x_total,y_total)
{

transfer_command_lcd(0x15); //Set Column Address
transfer_data_lcd(x);
transfer_data_lcd(x+x_total-1);

transfer_command_lcd(0x75); //Set Page Address
transfer_data_lcd(y);
transfer_data_lcd(y+y_total-1);

transfer_command_lcd(0x30);
transfer_command_lcd(0x5c);
}




void clear_screen(unsigned char c) 
{ 
int i,j; 
lcd_address(0,0,241,21); 
for(i=0;i<160;i++) 
{ 
for(j=0;j<256;j++) 
{ 
transfer_data_lcd(c); 
} 
} 
}







void test() 
{ 
unsigned int x;
unsigned int y;
unsigned int ca;
unsigned int color;
lcd_address(0,0,241,21); 

for(x=0;x<110;x++)       
{
transfer_data_lcd(0x00); 
}

for(y=0;y<161;y++)  
{
for(x=0;x<80;x++)  
{
ca++;
ca%=32;
color=(ca<<11)+(ca<<6) +ca ;
transfer_data_lcd(color>>8); 
transfer_data_lcd(color); 
}
ca=0;
for(x=0;x<96;x++) 
{
transfer_data_lcd(0x00); 
}
}
}


void main()
{
initial_lcd();
clear_screen(0xFF);
while(1)
{
test();
delay(1000);
clear_screen(0xFF); 
delay(1000);
clear_screen(0x00);
delay(1000);
}
}



