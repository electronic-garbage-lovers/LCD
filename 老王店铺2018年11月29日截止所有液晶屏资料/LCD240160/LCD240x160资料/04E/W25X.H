/*
STC12C单片机 硬件 SPI 读写 W25Q16 FLASH

2015-1-18测试

所有读操作都在应用程序中
2015-6-18
*/
#define W25P_WriteEnable 0x06
#define W25P_WriteDisable 0x04
#define W25P_ReadStatusReg 0x05
#define W25P_WriteStatusReg 0x01
#define W25P_ReadData  0x03
#define W25P_FastReadData 0x0B
#define W25P_PageProgram 0x02
#define W25P_SectorErase64k 0xD8 // 64KB
#define W25P_SectorErase32k	0x52 //32k
#define W25P_ChipErase  0xC7
#define W25P_PowerDown  0xB9
#define W25P_ReleasePowerDown 0xAB
#define W25P_DeviceID  0xAB
#define W25P_ManufactDeviceID 0x90


/*
unsigned char IO_Read_ID1()
{
 unsigned char byte;
 FLASH_CS = 0;
 IO_Send_Byte(W25P_DeviceID); 
 IO_Send_Byte(0);
 IO_Send_Byte(0);
 IO_Send_Byte(0);
 byte = IO_Get_Byte(); 
 FLASH_CS  = 1;
 return byte;
}
*/




////////////// 读取数据
/*
void IO_FastRead_nBytes(unsigned long Dst_Addr, unsigned char *prdata,unsigned int nBytes)
{
 unsigned int i = 0;
 FLASH_CS = 0;   
 SPI_RW(W25P_FastReadData);   
 SPI_RW(((Dst_Addr & 0xFFFFFF) >> 16)); 
 SPI_RW(((Dst_Addr & 0xFFFF) >> 8));
 SPI_RW(Dst_Addr & 0xFF);
 SPI_RW(0xFF);  
 for (i = 0; i < nBytes; i++)
 {
  prdata[i] = SPI_RW(0xff);
 }
 FLASH_CS = 1;   
}

*/

/*

unsigned char IO_Read_StatusReg()
{
 unsigned char byte = 0;
 FLASH_CS = 0;   
 SPI_RW(W25P_ReadStatusReg); // send Read Status Register command
 byte = SPI_RW(0xff);   // receive byte 
 FLASH_CS = 1;    // disable device
 return byte;
}




void IO_Wait_Busy()
{

 while (IO_Read_StatusReg() == 0x03)
  IO_Read_StatusReg();
}

void IO_Write_Enable()
{
 FLASH_CS = 0;   
 SPI_RW(W25P_WriteEnable); 
 FLASH_CS = 1;   
}


void IO_Erase_Chip()
{
 FLASH_CS = 0;    // enable device 
 IO_Write_Enable();    // set WEL 
 FLASH_CS = 0;
 IO_Wait_Busy();
 FLASH_CS = 0;
 SPI_RW(W25P_ChipErase);  // send Chip Erase command 
 FLASH_CS = 1;    // disable device 
 IO_Wait_Busy();
}




//*******************************************************************************
//* Function Name  : SPI_WQ_FLASH_PageWrite
//* Description    : 叶写W25Q80芯片（最大256字节）
//* Input          : pBuffer代写入数据，WriteAddr写入首地址，NumByteToWrite 长度
//* Output         : 无
//* Return         : 无
//*******************************************************************************
void IO_Write_page( unsigned long Dst_Addr,unsigned char* pBuffer, unsigned int NumByteToWrite)
{ 
 FLASH_CS = 0;     // enable device 
 IO_Write_Enable();    // set WEL 
 FLASH_CS = 0;
 SPI_RW(W25P_PageProgram);   // send Byte Program command 
 SPI_RW(((Dst_Addr & 0xFFFFFF) >> 16)); // send 3 address bytes
 SPI_RW(((Dst_Addr & 0xFFFF) >> 8));
 SPI_RW(Dst_Addr & 0xFF);
 	 while (NumByteToWrite--)
	 {
	  SPI_RW(*pBuffer);  // send byte to be programmed 
	  pBuffer++;
	 } 
 FLASH_CS = 1;    // disable device 
 IO_Wait_Busy();
 DelayMs(10);
}




*/
