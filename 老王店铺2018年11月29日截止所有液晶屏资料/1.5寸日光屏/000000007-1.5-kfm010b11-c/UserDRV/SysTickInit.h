#ifndef _SYSTICKINIT_H_
#define _SYSTICKINIT_H_
#include "configALL.H"
void SysTickInit(void);
void SysTickDelay1MS(uint32_t delayNms);
void SysTickDelay1Us(uint32_t delayNus);
#endif

