#ifndef _IIC_H_
#define _IIC_H_

#include "MacroAndConst.h"

extern void iic_init(void);
extern void iic_start(void);
extern void iic_stop(void);
extern bool iic_wait_for_ack(void);
extern void iic_ack(void);
extern void iic_nack(void);
extern void iic_write_byte(uint8_t chData);
extern uint8_t iic_read_byte(uint8_t chAck);

extern void iic_write_one_byte(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chData);
extern bool iic_write_buffer(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chNum, uint8_t *pchBuffer);
extern uint8_t iic_read_one_byte(uint8_t chDevAddr, uint8_t chRegAddr);
extern bool iic_read_buffer(uint8_t chDevAddr, uint8_t chRegAddr, uint8_t chNum, uint8_t *pchBuffer);


#endif

