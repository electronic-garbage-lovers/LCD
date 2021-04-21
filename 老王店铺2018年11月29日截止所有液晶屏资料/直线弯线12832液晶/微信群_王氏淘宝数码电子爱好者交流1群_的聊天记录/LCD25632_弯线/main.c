#include "SPI_ST75256.h"

void main(void)
{
	unsigned char i=0;
	P1M0 |= 0x1F;P1M1 &= 0xE0;         //推挽
		ST75256_Init();			//初始化OLED  
		ST75256_ShowString(0,0,"Zeng Hui OLED TEST");
		ST75256_ShowString(0,1,"2018-07-19");
		ST75256_ShowString(0,2,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkimnopqrstuvwxyz");
//	for (i=0;i<20;i++)
//		{
//			ST75256_ShowString(0,i,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkimnopqrstuvwxyz");
//		}
	while(1);
	{		
//		ST75256_ShowString(0,0,"Zeng Hui OLED TEST");
		
		/*
		for (i=0;i<4;i++)
		{
			Delay_mS(2000);
			ST75256_Init();			//初始化OLED  
			ST75256_ShowString(0,i,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkimnopqrstuvwxyz");
		}
*/
	}	  	
}
	