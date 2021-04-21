#include "SPI_ST75256.h"

void main(void)
{
		ST75256_Init();			//≥ı ºªØOLED  
		ST75256_ShowString(0,0,"Zeng Hui LCD TEST");
		ST75256_ShowString(0,1,"2018-09-25");
		ST75256_ShowString(0,2,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkimnopqrstuvwxyz");

	while(1);
}
	