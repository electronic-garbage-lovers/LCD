#ifndef _LED0_H_
#define _LED0_H_
#define LED0    *((uint32_t *) (( GPIOA_BASE +0x0c-0x40000000 )*32+8*4+0x42000000))  //GPIOA_DOR bit8 add
#define open_LED0()  GPIOA->BSRR |=(uint32_t) (1<<8);//PA8����
#define  off_LED0()  GPIOA->BRR |=(uint32_t) (1<<8);//PA8��λ
#define LED0_Negate() LED0 = ~LED0                  //PA8ȡ��
#endif
