/*-----------------------
      SPI 部分




------------------------*/
// 如果定义 SPI，做启用STC12的硬件SPI
#define SPI



// STC12 的硬件SPI

sfr SPSTAT      =   0xcd;       //SPI status register
#define SPIF        0x80        //SPSTAT.7
#define WCOL        0x40        //SPSTAT.6
sfr SPCTL       =   0xce;       //SPI control register
#define SSIG        0x80        //SPCTL.7
#define SPEN        0x40        //SPCTL.6
#define DORD        0x20        //SPCTL.5
#define MSTR        0x10        //SPCTL.4
#define CPOL        0x08        //SPCTL.3
#define CPHA        0x04        //SPCTL.2
#define SPDHH       0x00        //CPU_CLK/4
#define SPDH        0x01        //CPU_CLK/16
#define SPDL        0x02        //CPU_CLK/64
#define SPDLL       0x03        //CPU_CLK/128
sfr SPDAT       =   0xcf;       //SPI data register





/*********************************************/
/* 函数功能：硬件SPI发送byte，接收一个字节   */
/*********************************************/
unsigned char SPI_RW(unsigned char byte)
{
#ifdef SPI
    SPDAT = byte;                //trigger SPI send
    while (!(SPSTAT & SPIF));   //wait send complete
    SPSTAT = SPIF | WCOL;       //clear SPI status
    return SPDAT;               //return received SPI data
#else
	unsigned char bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)  // 输出8位
	{
		NRF_MOSI=(byte&0x80); 			// MSB TO MOSI
		byte=(byte<<1);					// shift next bit to MSB
		NRF_SCK=1;
		byte|=NRF_MISO;	        		// capture current MISO bit
		NRF_SCK=0;
	}
	return byte;
#endif
}



/*********************************************/
/*         STC12硬件 SPI 主机初始化          */
/*********************************************/
void InitSPI()
{
#ifdef SPI
    SPDAT = 0;                  //initial SPI data
    SPSTAT = SPIF | WCOL;       //clear SPI status
    SPCTL = SPEN | MSTR | SSIG ;        //master mode
#else
    SPI_RW(0xff);
#endif
}








