#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

void LED_Init(void);
void LED_Tick(void);
void KEY_Init(void);
//uint8_t KEY_Scan(void);

#endif
