#include "LIB_Config.h"
#include "IIC.h"


enum {
	IIC_DIR_TX = 0,
	IIC_DIR_RX,
};

enum {
	IIC_SDA_IN = 0,
	IIC_SDA_OUT
};

enum {
	IIC_ACK = 0,
	IIC_NACK
};

void iic_init(void)
{
	__IIC_SCL_SET();
	__IIC_SDA_SET();
	delay_ms(1);
}

void iic_start(void)
{
	__IIC_SDA_OUT();
	__IIC_SDA_SET();
	__IIC_SCL_SET();//
	delay_us(1);
	__IIC_SDA_CLR();
	delay_us(1);
	__IIC_SCL_CLR();
	delay_us(1);
}

void iic_stop(void)
{
	__IIC_SCL_CLR();
	__IIC_SDA_CLR();
	delay_us(1);
	__IIC_SCL_SET();
	delay_us(1);
	__IIC_SDA_SET();
	delay_us(1);
}

void iic_ack(void)
{
	__IIC_SCL_CLR();
	__IIC_SDA_OUT();
	__IIC_SDA_CLR();
	delay_us(1);
	__IIC_SCL_SET();
	delay_us(1);
	__IIC_SCL_CLR();
}

void iic_nack(void)
{
	__IIC_SCL_CLR();
	__IIC_SDA_OUT();
	__IIC_SDA_SET();
	delay_us(1);
	__IIC_SCL_SET();
	delay_us(1);
	__IIC_SCL_CLR();
}

bool iic_wait_for_ack(void)
{
	uint8_t chTimeOut = 0;
	
	__IIC_SCL_CLR();
	//delay_us(1);
	__IIC_SCL_SET();
	
	//__IIC_SDA_IN();
	while ((!(__IIC_SDA_READ())) && (chTimeOut ++)) {
		chTimeOut ++;
		if (chTimeOut > 200) {
			chTimeOut = 0;
			iic_stop();
			return false;
		}
	}
	__IIC_SCL_CLR();
	//delay_us(1);
	
	return true;
}

void iic_write_byte(uint8_t chData)
{
	uint8_t i;
	
	__IIC_SDA_OUT();
	for(i = 0; i < 8; i ++) {
		__IIC_SCL_CLR();
		//delay_us(1);
		if(chData & 0x80) {
			__IIC_SDA_SET();
		} else {
			__IIC_SDA_CLR();
		}
		chData <<= 1;
		//delay_us(1);
		__IIC_SCL_SET();
		delay_us(1);
	}
}

void iic_write_one_byte(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chData)
{
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_TX);
	iic_wait_for_ack();
	iic_write_byte(chRegAddr);
	iic_wait_for_ack();
	iic_write_byte(chData);
	iic_wait_for_ack();
	iic_stop();
}

bool iic_write_buffer(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chNum, uint8_t *pchBuffer)
{
	uint8_t i;

	if (0 == chNum || NULL == pchBuffer) {
		return false;
	}
	
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_TX);
	iic_wait_for_ack();
	iic_write_byte(chRegAddr);
	iic_wait_for_ack();
	
	for (i = 0; i < chNum; i ++) {
		iic_write_byte(*(pchBuffer + i));
		iic_wait_for_ack();
	}
	iic_stop();

	return true;
}

uint8_t iic_read_byte(uint8_t chAck)
{
	uint8_t i, chRecData = 0;

	__IIC_SDA_IN();
	for (i = 0; i < 8; i ++) {
		__IIC_SCL_CLR();
		//delay_us(1);
		__IIC_SCL_SET();
		chRecData <<= 1;
		if(__IIC_SDA_READ())
			chRecData |= 0x01;
		else
			chRecData &= ~0x01;
		//delay_us(1);
	}
	
	if (IIC_ACK == chAck) {
		iic_ack();
	} else {
		iic_nack();
	}
	
	return chRecData;
}

uint8_t iic_read_one_byte(uint8_t chDevAddr, uint8_t chRegAddr)
{
	uint8_t chTemp = 0;
	
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_TX);
	iic_wait_for_ack();
	iic_write_byte(chRegAddr);
	iic_wait_for_ack();
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_RX);
	iic_wait_for_ack();
	chTemp = iic_read_byte(IIC_NACK);
	iic_stop();
	
	return chTemp;
}

bool iic_read_buffer(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chNum, uint8_t *pchBuffer)
{
	uint8_t i;

	if (0 == chNum || NULL == pchBuffer) {
		return false;
	}
	
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_TX);
	iic_wait_for_ack();
	iic_write_byte(chRegAddr);
	iic_wait_for_ack();
	iic_start();
	iic_write_byte(chDevAddr | IIC_DIR_RX);
	iic_wait_for_ack();

	for (i = 0; i < chNum; i ++) {
		if ((chNum - 1) == i) {
			*(pchBuffer + i) = iic_read_byte(IIC_NACK);
		} else {
			*(pchBuffer + i) = iic_read_byte(IIC_ACK);
		}
	}

	iic_stop();
	
	return true;
}

/*
void Delay_us(uint16_t Time)
{
	uint8_t i;
	
	while(Time --) for(i = 0; i < 10; i ++);
}

void Delay_ms(uint16_t Time)
{
	while(Time --) Delay_us(1000);
}
*/

