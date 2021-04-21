#ifndef _KeyProcess_h_
#define _KeyProcess_h_
#define Key7    *((uint32_t *) (( GPIOC_BASE +0x08-0x40000000 )*32+7*4+0x42000000))  //GPIOc_iOR bit7 add
extern volatile uint8_t Keypad; ;
inline void InitKeyPort(void);
void ScanKey(void);
void ScanKey1(void);
#endif
