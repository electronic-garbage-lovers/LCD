#include <string.h>
#include <intrins.H>
#include "STC15W408.h"

//*****************************
//引脚定义 COMSCN脚接电源
//*****************************
#define SPI_CSB   P10
#define SPI_A0    P11
#define SPI_RST   P12
#define SPI_SCL   P13
#define SPI_SDA   P14

#define SPI_COMMAND  0
#define SPI_DATA     1

void Delay_mS(unsigned int mS);		//@11.0592MHz
void ST75256_ShowString(unsigned char x,unsigned char y,unsigned char *chr);
void ST75256_Clear(void);
void ST75256_Init(void);
void SPI_SendByte(bit COMMAND,unsigned char dat);
