/*
LCD 240 x 160 3.5��32���Ҷ�����������

��������STC89C54RD+ PDIP40 11.0592MHz�ϵ���ͨ��
P0��10K����������VCC +5v

2018-11-15 
ʫ֯��Ե.�細����
*/



/*------------------
       delay
-------------------*/
void delay(unsigned int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<110;k++);
}
void delay_us(unsigned int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<2;k++);
}

/*------------------
      д����
-------------------*/
void transfer_command_lcd(int data1)
{
lcd_rs=0;
P0=data1;
_nop_();  //�������ȥ��
lcd_en=1;
lcd_en=0;
}

/*------------------
      д����
-------------------*/
void transfer_data_lcd(int data1)
{
lcd_rs=1;
P0=data1;
_nop_(); //�������ȥ��
lcd_en=1;
lcd_en=0;
}

/*------------------
      ��ʼ��
-------------------*/
void initial_lcd()
{
lcd_wr=0;   
lcd_cs=0;  
lcd_reset=0;
delay(50);  
lcd_reset=1;
delay(600); 
transfer_command_lcd(0x30); //EXT=0 
transfer_command_lcd(0x94); //Sleep out 
transfer_command_lcd(0x31); //EXT=1 
transfer_command_lcd(0xD7); //Autoread disable 
transfer_data_lcd(0X9F); // 
transfer_command_lcd(0x32); //Analog SET 
transfer_data_lcd(0x00); //OSC Frequency adjustment 
transfer_data_lcd(0x01); //Frequency on booster capacitors->6KHz 
transfer_data_lcd(0x03); //Bias=1/13 
transfer_command_lcd(0x20);
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
transfer_command_lcd(0x30);
transfer_command_lcd(0x75);
transfer_data_lcd(0X00);
transfer_data_lcd(0X14); 
transfer_command_lcd(0x15); 
transfer_data_lcd(0X00);
transfer_data_lcd(0Xef);
transfer_command_lcd(0xbc);
transfer_data_lcd(0x02);
transfer_command_lcd(0xCA);
transfer_data_lcd(0X00);
transfer_data_lcd(0X9F);
transfer_data_lcd(0X20);
transfer_command_lcd(0xF0);
transfer_data_lcd(159);
transfer_command_lcd(0x81); 
transfer_data_lcd(0x98); 

transfer_data_lcd(0x03);
transfer_command_lcd(0x20);
transfer_data_lcd(0x0B);
delay_us(120); 
transfer_command_lcd(0xAF); 
}


/*-------------------------
  ������ĻҶ�ת16λ����
----------------=--------*/
unsigned int encode(unsigned char d1,unsigned char d2, unsigned char d3)
{
 return (d3<<11)+(d2<<6) +d1 ;
}

/*------------------
       λ��
-------------------*/
void locate(unsigned char x, unsigned char y)
{
x+=24;
y=159-y;
transfer_command_lcd(x&0x0f);
transfer_command_lcd(0x10|(x>>4));
transfer_command_lcd(0x60+(y&0x0f));
transfer_command_lcd(0x70+(y>>4));
}


/*------------------
     ȫ�����
-------------------*/
void cls(unsigned int c)
{
unsigned char y,j;
for(y=0;y<160;y++)
 {
  locate(0,y);
  for(j=0;j<80;j++)
   {
    transfer_data_lcd(c>>8);
    transfer_data_lcd(c);
   }
 }
}




