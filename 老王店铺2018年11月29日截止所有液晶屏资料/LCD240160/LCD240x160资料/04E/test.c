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


/*��ʱ��1 �����i ��*/
void delay(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<510;k++);
}
/*��ʱ��1us ��i ��*/
void delay_us(int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<10;k++);
}

//���ڷ�ʽ
//дָ�LCD ģ��
void transfer_command_lcd(int data1)
{
lcd_rs=0;
lcd_en=1;
P0=data1;P0=data1;P0=data1;P0=data1;
lcd_en=0;
}

//д���ݵ�LCD ģ��
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
transfer_command_lcd(0x20); //�Ҷ����� 
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
transfer_command_lcd(0x30); //EXT1=0��EXT0=0,��ʾѡ���ˡ���չָ��� 1�� 
transfer_command_lcd(0x75); //ҳ��ַ���� 
transfer_data_lcd(0X00); //��ʼҳ��ַ��YS=0X00 
transfer_data_lcd(0X14); //����ҳ��ַ��YE=0x1Fÿ 4 ��Ϊһҳ���� 0��3 ��Ϊ�� 0 ҳ���� 124��127 ��Ϊ�� 31 ҳ��31=0x1f�� 
transfer_command_lcd(0x15); //�е�ַ���� 
transfer_data_lcd(0X00); //��ʼ�е�ַ��XS=0 
transfer_data_lcd(0Xef); //�����е�ַ��XE=240��0xef�� 
transfer_command_lcd(0xbc); //����ɨ�跽�� 
transfer_data_lcd(0x02); //MX.MY=Normal 
// transfer_command_lcd(0x0c); //���ݸ�ʽѡ��,0x0C �ǵ�λ��ǰ D0-D7,0x08 �Ǹ�λ��ǰ D7-D0 
transfer_command_lcd(0xCA); //��ʾ���� 
transfer_data_lcd(0X00); //���� CL ����Ƶ�ʣ�CLD=0 
transfer_data_lcd(0X9F); //ռ�ձȣ�Duty=160 
transfer_data_lcd(0X20); //N �з��ԣ�Nline=off 
transfer_command_lcd(0xF0); //��ʾģʽ 
transfer_data_lcd(159); //�����Ϊ 0x11����ʾѡ�� 4 �Ҷȼ�ģʽ�������Ϊ 0x10:��ʾѡ��ڰ�ģʽ 
transfer_command_lcd(0x81); //���öԱȶȣ���0x81�����ɸĶ��������ŵ� 2 �������ǿɸĵģ�������΢����ֵ����� 
transfer_data_lcd(0x80);  //΢���Աȶ�,�ɵ���Χ 0x00��0x3f���� 64 �� 0
transfer_data_lcd(0x03); //�ֵ��Աȶ�,�ɵ���Χ 0x00��0x07���� 8 �� 
transfer_command_lcd(0x20); //��Դ���� 
transfer_data_lcd(0x0B); //D0=regulator ; D1=follower ; D3=booste, on:1 off:0 
delay_us(200); 
transfer_command_lcd(0xAF); //����ʾ 
}





/*дLCD ���е�ַ��X Ϊ��ʼ���е�ַ��Y Ϊ��ʼ���е�ַ��x_total,y_total �ֱ�Ϊ�е�ַ���е�ַ����㵽�յ�Ĳ�ֵ */
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



